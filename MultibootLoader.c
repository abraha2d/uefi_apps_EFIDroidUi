/** @file

Copyright (c) 2004 - 2008, Intel Corporation. All rights reserved.<BR>
Copyright (c) 2014, ARM Ltd. All rights reserved.<BR>

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "EFIDroidUi.h"

EFI_STATUS
MultibootCallback (
  IN MENU_ENTRY *This
)
{
  EFI_STATUS                Status;
  multiboot_handle_t        *mbhandle = This->Private;
  EFI_FILE_PROTOCOL         *BootFile;

  DEBUG((EFI_D_ERROR, "Booting %a ...\n", mbhandle->Name));

  // open ROM directory
  Status = mbhandle->ROMDirectory->Open (
                   mbhandle->ROMDirectory,
                   &BootFile,
                   mbhandle->PartitionBoot,
                   EFI_FILE_MODE_READ,
                   0
                   );
  if (EFI_ERROR (Status)) {
    UINTN Len = StrLen(mbhandle->PartitionBoot)+100;
    CHAR8* Buf = AllocatePool(Len);
    AsciiSPrint(Buf, Len, "Can't open %s", mbhandle->PartitionBoot);
    MenuShowMessage("Error", Buf);
    return Status;
  }

  return AndroidBootFromFile(BootFile, mbhandle, FALSE);
}
