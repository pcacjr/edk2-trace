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
#include <trace.h>
#include <compiler.h>

#define _FUNCTION_PROTO(s)                      \
  STATIC                                        \
  VOID __noinline                               \
  __func_##s (                                  \
    VOID                                        \
  )

#define DECLARE_FUNCTION(s) \
  _FUNCTION_PROTO(s);

#define FUNCTION_IMPL(s) \
  _FUNCTION_PROTO(s)

#define CALL_FUNCTION(s)                            \
  do {                                              \
    fprintf (stderr, "Call __func_" # s "()\n");    \
    __func_##s ();                                  \
  } while (0)

//
// Start test
//
DECLARE_FUNCTION (start) 

//
// End test
//
DECLARE_FUNCTION (end)

DECLARE_FUNCTION (a)
DECLARE_FUNCTION (b)
DECLARE_FUNCTION (c)
DECLARE_FUNCTION (d)
DECLARE_FUNCTION (e)
DECLARE_FUNCTION (f)
DECLARE_FUNCTION (g)
DECLARE_FUNCTION (h)

FUNCTION_IMPL(start)
{
  CALL_FUNCTION (a);
}

FUNCTION_IMPL(a)
{
  CALL_FUNCTION (b);
}

FUNCTION_IMPL(b)
{
  CALL_FUNCTION (c);
}

FUNCTION_IMPL(c)
{
  CALL_FUNCTION (d);
}

FUNCTION_IMPL(d)
{
  CALL_FUNCTION (e);
}

FUNCTION_IMPL(e)
{
  CALL_FUNCTION (f);
}

FUNCTION_IMPL(f)
{
  CALL_FUNCTION (g);
}

FUNCTION_IMPL(g)
{
  CALL_FUNCTION (h);
}

FUNCTION_IMPL(h)
{
  CALL_FUNCTION (end);
}

FUNCTION_IMPL(end)
{
  DumpCallStack (
    AsmGetStackPointerAddress (),
    AsmGetFramePointerAddress (),
    AsmGetCurrentIpAddress ()
    );
}

#define TEST_START()                            \
  do {                                          \
    fprintf(stderr, "Start test:\n\n");         \
    CALL_FUNCTION (start);                      \
  } while (0)

int
main (
  IN int Argc __unused,
  IN char *Argv[] __unused
  )
{
  TEST_START ();
  return 0;
}
