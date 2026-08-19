#ifndef EFI_H
#define EFI_H

/* Basic UEFI types (MIPS32 LE) */
typedef unsigned long long  UINT64;
typedef long long           INT64;
typedef unsigned int        UINT32;
typedef int                 INT32;
typedef unsigned short      UINT16;
typedef short               INT16;
typedef unsigned char       UINT8;
typedef char                INT8;
typedef unsigned int        UINTN;
typedef int                 INTN;
typedef void                VOID;
typedef UINT8               BOOLEAN;
typedef UINT16              CHAR16;
typedef UINTN               EFI_STATUS;
typedef VOID               *EFI_HANDLE;

#define EFI_SUCCESS  0
#define TRUE         1
#define FALSE        0

#ifndef NULL
#define NULL ((void *)0)
#endif

/* Forward decls */
struct _EFI_SYSTEM_TABLE;
struct _EFI_BOOT_SERVICES;

typedef struct _EFI_SYSTEM_TABLE   EFI_SYSTEM_TABLE;
typedef struct _EFI_BOOT_SERVICES  EFI_BOOT_SERVICES;

struct _EFI_SYSTEM_TABLE {
    UINT64 Signature;          /* "IBI SYST" */
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    VOID *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    VOID *ConOut;
    EFI_HANDLE StandardErrorHandle;
    VOID *StdErr;
    VOID *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    VOID *ConfigurationTable;
};

struct _EFI_BOOT_SERVICES {
    UINT64 Signature;          /* "BOOTSERV" */
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
    VOID *RaiseTPL;
    VOID *RestoreTPL;
    VOID *AllocatePages;
    VOID *FreePages;
    VOID *GetMemoryMap;
    VOID *AllocatePool;
    VOID *FreePool;
    /* rest left NULL for now */
};

/* Public interface */
void efi_init(void);
EFI_SYSTEM_TABLE *efi_get_system_table(void);

#endif /* EFI_H */