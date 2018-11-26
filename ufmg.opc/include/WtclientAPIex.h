

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

//
// ChangeBrowsePosition (...)
//
// Calls the IOPCBrowseServerAddressSpace::ChangeBrowsePosition
// Interface for the defined Server Connection.
// BrowseDirection may be OPC_BROWSE_UP, OPC_BROWSE_DOWN or OPC_BROWSE_TO
//
_declspec(dllexport) HRESULT  WINAPI ChangeBrowsePosition (HANDLE hConnect, DWORD BrowseDirection, LPWSTR NodeName);

//
// BrowseOPCItemIDs (...)
//
// Calls the IOPCBrowseServerAddressSpace::BrowseOPCItemIDs
// Interface for the defined Server Connection.
//
_declspec(dllexport) HRESULT  WINAPI BrowseOPCItemIDs (HANDLE hConnect, OPCBROWSETYPE BrowseType, LPWSTR Filter, VARTYPE DataType, DWORD Access, LPENUMSTRING	*pIEnumString);


//
// SyncIO_Write(...)
//
// Allows the controlling application to write to a list of defined OPC items
// using the IOPCSyncIO::Write Interface.
//
//	Application may write multiple item values with a single command.
//  Application must insure that pItems, pVars, and pErrors arrays are at least NumbrItems long.
//  WTClient DLL will copy error list from server supplied memory buffer into pErrors
//	array as supplied by application and then free the memory allocated by the opc server.
//
_declspec(dllexport) HRESULT  WINAPI SyncIO_Write (HANDLE hConnect, HANDLE hGroup, int NumbrItems, OPCHANDLE *pItems, VARIANT *pVars, HRESULT *pErrors);


//
// SyncIO_Read(...)
//
// Allows the controlling application to read a list of defined OPC items
// using the IOPCSyncIO::Read Interface.
//
//
_declspec(dllexport) HRESULT  WINAPI SyncIO_Read (HANDLE hConnect, HANDLE hGroup, OPCDATASOURCE dwSource, DWORD dwCount, OPCHANDLE  *phServer, OPCITEMSTATE **ppItemValues, HRESULT **ppErrors);




#ifdef __cplusplus
}
#endif
