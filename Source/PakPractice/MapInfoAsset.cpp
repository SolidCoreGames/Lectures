// Fill out your copyright notice in the Description page of Project Settings.


#include "MapInfoAsset.h"

FString FMapInfo::GetLevelName() const
{
	return _name.ToString();
}

FText FMapInfo::GetLevelDescription() const
{
	return _description;
}

FString FMapInfo::GetLevelReference()
{
	if(!_primaryAssetLable)
	{
		_primaryAssetLable = Cast<UPrimaryAssetLabel>(FStringAssetReference(_primaryAsset).TryLoad());
	}

	if (_primaryAssetLable && _primaryAssetLable->ExplicitAssets.Num() > 0)
		return _primaryAssetLable->ExplicitAssets[0].GetLongPackageName();

	FString assetPath = _primaryAsset.GetAssetPathString();
	
	int32 dotPoint = assetPath.Find(".");
	assetPath = assetPath.Right(assetPath.Len() - dotPoint -1);
	return assetPath;
}
