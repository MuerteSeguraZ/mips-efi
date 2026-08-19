#include "efi/efi.h"
#include "uart.h"

static EFI_SYSTEM_TABLE gST;
static EFI_BOOT_SERVICES gBS;

static CHAR16 vendor[] = { 'M','I','P','S','-','E','F','I',0 };

void efi_init(void)
{
    /* Boot Services header */
    gBS.Signature = 0x56524553544f4f42ULL; /* "BOOTSERV" */
    gBS.Revision = 0x00010000;
    gBS.HeaderSize = sizeof(EFI_BOOT_SERVICES);
    gBS.CRC32 = 0;
    gBS.Reserved = 0;

    /* System Table header */
    gST.Signature = 0x5453595320494249ULL; /* "IBI SYST" */
    gST.Revision = 0x00010000;
    gST.HeaderSize = sizeof(EFI_SYSTEM_TABLE);
    gST.CRC32 = 0;
    gST.Reserved = 0;

    gST.FirmwareVendor = vendor;
    gST.FirmwareRevision = 0x00010000;

    gST.ConsoleInHandle = NULL;
    gST.ConIn = NULL;
    gST.ConsoleOutHandle = NULL;
    gST.ConOut = NULL;
    gST.StandardErrorHandle = NULL;
    gST.StdErr = NULL;

    gST.RuntimeServices = NULL;
    gST.BootServices = &gBS;

    gST.NumberOfTableEntries = 0;
    gST.ConfigurationTable = NULL;

    efi_console_init(&gST);
}

EFI_SYSTEM_TABLE *efi_get_system_table(void)
{
    return &gST;
}