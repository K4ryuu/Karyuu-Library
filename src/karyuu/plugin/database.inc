/***
 *    ██████╗  █████╗ ████████╗ █████╗ ██████╗  █████╗ ███████╗███████╗
 *    ██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝
 *    ██║  ██║███████║   ██║   ███████║██████╔╝███████║███████╗█████╗
 *    ██║  ██║██╔══██║   ██║   ██╔══██║██╔══██╗██╔══██║╚════██║██╔══╝
 *    ██████╔╝██║  ██║   ██║   ██║  ██║██████╔╝██║  ██║███████║███████╗
 *    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝
 */

#if defined _KARYUU_DATABASE_INCLUDED_
	#endinput
#endif
#define _KARYUU_DATABASE_INCLUDED_

stock int Karyuu_FetchIntByFieldName(Database hDatabase, DBResultSet hResult, const char[] sFieldName)
{
	int iFieldNum;
	hResult.FieldNameToNum(sFieldName, iFieldNum);

	return hResult.FetchInt(iFieldNum);
}

stock int Karyuu_FetchSringByFieldName(Database hDatabase, DBResultSet hResult, const char[] sFieldName, char[] sBuffer, int iLength)
{
	int iFieldNum;
	hResult.FieldNameToNum(sFieldName, iFieldNum);

	return hResult.FetchString(iFieldNum, sBuffer, iLength);
}

stock float Karyuu_FetchFloatByFieldName(Database hDatabase, DBResultSet hResult, const char[] sFieldName)
{
	int iFieldNum;
	hResult.FieldNameToNum(sFieldName, iFieldNum);

	return hResult.FetchFloat(iFieldNum);
}

stock bool Karyuu_FetchBoolByFieldName(Database hDatabase, DBResultSet hResult, const char[] sFieldName)
{
	int iFieldNum;
	hResult.FieldNameToNum(sFieldName, iFieldNum);

	return !!hResult.FetchInt(iFieldNum);
}