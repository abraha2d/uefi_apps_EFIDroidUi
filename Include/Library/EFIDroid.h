#ifndef __LIBRARY_EFIDROID_H__
#define __LIBRARY_EFIDROID_H__

#include <Uefi/UefiBaseType.h>

typedef struct {
  CONST CHAR8* Description;
  EFI_STATUS (*Callback) (VOID*);
  VOID *Private;
} BOOT_MENU_ENTRY;

VOID
EFIDroidEnterFrontPage (
  IN UINT16                 TimeoutDefault,
  IN BOOLEAN                ConnectAllHappened
  );

VOID
SetActiveMenu(
  BOOT_MENU_ENTRY* Menu
);

BOOT_MENU_ENTRY*
MenuCreate (
  VOID
);

BOOT_MENU_ENTRY*
MenuAddEntry (
  BOOT_MENU_ENTRY  **Menu,
  UINTN            *Size
);


EFI_STATUS
MenuFinish (
  BOOT_MENU_ENTRY  **Menu,
  UINTN            *Size
);

#endif
