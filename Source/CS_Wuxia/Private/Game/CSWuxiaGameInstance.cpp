// Copyright CS_WUXIA 


#include "Game/CSWuxiaGameInstance.h"

#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"

UCSWuxiaGameInstance::UCSWuxiaGameInstance()
{
	
}

FName UCSWuxiaGameInstance::GetStringTable(const FName& TableId, const FString& RowId) const
{
	// const FName StringTableKey = FName( "ST_CharacterName" );
	for ( TObjectPtr StringTable : StringTables)
	{
		if (!StringTable) continue;
		if (StringTable->GetName() != TableId) continue;
		// const FText OutDisplayName = FText::FromStringTable( TableId,RowId);
		const FStringTableConstRef StringTableRef = StringTable->GetStringTable();
		const FStringTableEntryConstPtr Entry = StringTableRef.Get().FindEntry( RowId );
		return FName(	Entry->GetSourceString());
	}
	UE_LOG(LogTemp, Error, TEXT("Failed to get %s string table rowId  %s"), *TableId.ToString(), *RowId);
	return FName();
}
