/** @file
*
*  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#ifndef __EFIDROIDUI_H__
#define __EFIDROIDUI_H__

#include <PiDxe.h>
#include <Protocol/BlockIo.h>
#include <Protocol/PartitionName.h>
#include <Protocol/EfiShellParameters.h>
#include <Protocol/EfiShell.h>
#include <Protocol/DevicePathFromText.h>
#include <Protocol/DevicePathToText.h>

#include <Library/ArmLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BdsLib.h>
#include <Library/DebugLib.h>
#include <Library/HiiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/ShellLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/GenericBdsLib.h>
#include <Library/DevicePathLib.h>
#include <Library/Cpio.h>
#include <Library/Decompress.h>
#include <Library/Ini.h>
#include <Library/PcdLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/FileHandleLib.h>
#include <Library/UEFIRamdisk.h>
#include <Library/Util.h>
#include <Library/Menu.h>

#include <LittleKernel.h>

#include "bootimg.h"

extern EFI_GUID gEFIDroidVariableGuid;

typedef struct {
  // ini values
  CHAR8  *Name;
  CHAR16 *PartitionBoot;

  // handles
  EFI_HANDLE DeviceHandle;
  EFI_FILE_PROTOCOL* ROMDirectory;

  // set by MultibootCallback
  CHAR8* MultibootConfig;
} multiboot_handle_t;

typedef struct {
  EFI_BLOCK_IO_PROTOCOL *BlockIo;
  EFI_FILE_PROTOCOL     *File;
  multiboot_handle_t    *mbhandle;
} MENU_ENTRY_PDATA;

#define RECOVERY_MENU_SIGNATURE             SIGNATURE_32 ('r', 'e', 'c', 'm')

typedef struct {
  UINTN           Signature;
  LIST_ENTRY      Link;

  MENU_OPTION     *SubMenu;
  MENU_ENTRY      *RootEntry;
  MENU_ENTRY      *BaseEntry;
} RECOVERY_MENU;

EFI_STATUS
AndroidBootFromBlockIo (
  IN EFI_BLOCK_IO_PROTOCOL  *BlockIo,
  IN multiboot_handle_t     *mbhandle
);

EFI_STATUS
AndroidBootFromFile (
  IN EFI_FILE_PROTOCOL  *File,
  IN multiboot_handle_t *mbhandle
);

EFI_STATUS
AndroidVerify (
  IN VOID* Buffer
);

CPIO_NEWC_HEADER*
AndroidGetDecompRamdiskFromBlockIo (
  IN EFI_BLOCK_IO_PROTOCOL  *BlockIo,
  IN boot_img_hdr_t* AndroidHdr
);

EFI_STATUS
MultibootCallback (
  IN VOID *Private
);

#endif /* __EFIDROIDUI_H__ */