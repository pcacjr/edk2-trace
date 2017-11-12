/*
 * Copyright (c) 2017 Paulo Alcantara
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of other contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>

#include <uefi.h>
#include <asm.h>
#include <pe.h>
#include <compiler.h>

#include "trace.h"

//
// PE/COFF executable image base address. The weak symbol is created by linker.
//
extern char __image_base__;

/**
  Find PE/COFF image base address based on current IP address.

  @param[in]  CurrentEip  Current IP address.

  @retval     Value       PE/COFF image base address.

**/
STATIC
UINTN
GetImageBaseAddressFromPeImage (
  IN UINTN CurrentEip __unused
  )
{
  return (UINTN)&__image_base__;
}

/**
  Dump out stack contents.

  @param[in] CurrentStackPointerAddress Current stack pointer address.
  @param[in] UnwondStacksCount          Count of unwond stack frames.

  @retval    None

**/
STATIC
VOID
DumpStackContents (
  IN UINTN CurrentStackPointerAddress,
  IN INTN UnwondStacksCount
  )
{
  fprintf (stderr, "\nStack dump:\n");

  while (UnwondStacksCount -- > 0) {
    fprintf (
      stderr,
      "0x%016lx:  %016lx %016lx\n",
      (unsigned long)CurrentStackPointerAddress,
      (unsigned long)(*(UINTN *)CurrentStackPointerAddress),
      (unsigned long)(*(UINTN *)(CurrentStackPointerAddress + sizeof (UINTN)))
      );

    CurrentStackPointerAddress = AsmGetNextStackPointerAddress (
      CurrentStackPointerAddress
      );
  }
}

/**
  Dump out call stack.

  @param[in] CurrentStackPointerAddress  Current stack pointer address.
  @param[in] CurrentFramePointerAddress  Current frame pointer address.
  @param[in] CurrentIpAddress            Current IP address.

  @retval    None

**/
VOID
DumpCallStack (
  IN UINTN CurrentStackPointerAddress,
  IN UINTN CurrentFramePointerAddress,
  IN UINTN CurrentIpAddress
  )
{
  UINTN ImageBaseAddress;
  INTN UnwondStacksCount;

  ImageBaseAddress = GetImageBaseAddressFromPeImage (CurrentIpAddress);
  ASSERT (ImageBaseAddress != 0);

  UnwondStacksCount = 0;

  fprintf (stderr, "\nCallstack:\n");
  for (;;) {
    //
    // Print call frame information
    //
    fprintf (
      stderr,
      "%d 0x%016lx in main (+0x%x) (0x%016lx)\n",
      (int)UnwondStacksCount,
      (unsigned long)CurrentIpAddress,
      (int)(CurrentIpAddress - ImageBaseAddress - 1),
      (unsigned long)CurrentFramePointerAddress
      );

    //
    // Get last IP address (aka return address) and check if it's outside
    // PE/COFF image base address.
    //
    CurrentIpAddress = AsmGetReturnAddress (CurrentFramePointerAddress);
    if (CurrentIpAddress < ImageBaseAddress) {
      //
      // We've got end of call stack. Stop trace.
      //
      break;
    }

    //
    // Unwind the stack
    //
    CurrentFramePointerAddress = AsmGetLastFramePointerAddress (
      CurrentFramePointerAddress
      );

    //
    // Update number of unwound stack frames
    //
    UnwondStacksCount++;
  }

  //
  // Dump out stack contents
  //
  DumpStackContents (CurrentStackPointerAddress, UnwondStacksCount);
}
