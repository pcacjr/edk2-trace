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

#ifndef _PE_H
#define _PE_H

#include <uefi.h>

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16

#pragma pack(1)

typedef struct {
  UINT16 e_magic;         // Magic number
  UINT16 e_cblp;          // Bytes on last page of file
  UINT16 e_cp;            // Pages in file
  UINT16 e_crlc;          // Relocations
  UINT16 e_cparhdr;       // Size of header in paragraphs
  UINT16 e_minalloc;      // Minimum extra paragraphs needed
  UINT16 e_maxalloc;      // Maximum extra paragraphs needed
  UINT16 e_ss;            // Initial (relative) SS value
  UINT16 e_sp;            // Initial SP value
  UINT16 e_csum;          // Checksum
  UINT16 e_ip;            // Initial IP value
  UINT16 e_cs;            // Initial (relative) CS value
  UINT16 e_lfarlc;        // File address of relocation table
  UINT16 e_ovno;          // Overlay number
  UINT16 e_res[4];        // Reserved words
  UINT16 e_oemid;         // OEM identifier (for e_oeminfo)
  UINT16 e_oeminfo;       // OEM information; e_oemid specific
  UINT16 e_res2[10];      // Reserved words
  UINT32 e_lfanew;        // File address of new exe header
} IMAGE_DOS_HEADER;

typedef struct {
  UINT16  Machine;
  UINT16  NumberOfSections;
  UINT32  TimeDateStamp;
  UINT32  PointerToSymbolTable;
  UINT32  NumberOfSymbols;
  UINT16  SizeOfOptionalHeader;
  UINT16  Characteristics;
} IMAGE_FILE_HEADER;

typedef struct {
  UINT32 VirtualAddress;
  UINT32 Size;
} IMAGE_DATA_DIRECTORY;

typedef struct {
  UINT16       Magic;
  UINT8        MajorLinkerVersion;
  UINT8        MinorLinkerVersion;
  UINT32       SizeOfCode;
  UINT32       SizeOfInitializedData;
  UINT32       SizeOfUninitializedData;
  UINT32       AddressOfEntryPoint;
  UINT32       BaseOfCode;
  UINT64       ImageBase;
  UINT32       SectionAlignment;
  UINT32       FileAlignment;
  UINT16       MajorOperatingSystemVersion;
  UINT16       MinorOperatingSystemVersion;
  UINT16       MajorImageVersion;
  UINT16       MinorImageVersion;
  UINT16       MajorSubsystemVersion;
  UINT16       MinorSubsystemVersion;
  UINT32       Win32VersionValue;
  UINT32       SizeOfImage;
  UINT32       SizeOfHeaders;
  UINT32       CheckSum;
  UINT16       Subsystem;
  UINT16       DllCharacteristics;
  UINT64       SizeOfStackReserve;
  UINT64       SizeOfStackCommit;
  UINT64       SizeOfHeapReserve;
  UINT64       SizeOfHeapCommit;
  UINT32       LoaderFlags;
  UINT32       NumberOfRvaAndSizes;
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER64;

typedef struct {
  UINT16                Magic;
  UINT8                 MajorLinkerVersion;
  UINT8                 MinorLinkerVersion;
  UINT32                SizeOfCode;
  UINT32                SizeOfInitializedData;
  UINT32                SizeOfUninitializedData;
  UINT32                AddressOfEntryPoint;
  UINT32                BaseOfCode;
  UINT32                BaseOfData;
  UINT32                ImageBase;
  UINT32                SectionAlignment;
  UINT32                FileAlignment;
  UINT16                MajorOperatingSystemVersion;
  UINT16                MinorOperatingSystemVersion;
  UINT16                MajorImageVersion;
  UINT16                MinorImageVersion;
  UINT16                MajorSubsystemVersion;
  UINT16                MinorSubsystemVersion;
  UINT32                Win32VersionValue;
  UINT32                SizeOfImage;
  UINT32                SizeOfHeaders;
  UINT32                CheckSum;
  UINT16                Subsystem;
  UINT16                DllCharacteristics;
  UINT32                SizeOfStackReserve;
  UINT32                SizeOfStackCommit;
  UINT32                SizeOfHeapReserve;
  UINT32                SizeOfHeapCommit;
  UINT32                LoaderFlags;
  UINT32                NumberOfRvaAndSizes;
  IMAGE_DATA_DIRECTORY  DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER;

#pragma pack()

typedef IMAGE_OPTIONAL_HEADER IMAGE_OPTIONAL_HEADER32;

#define IMAGE_NT_OPTIONAL_HDR32_MAGIC 0x10b
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC 0x20b

#endif // _PE_H
