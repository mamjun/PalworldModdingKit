#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EPalLogPriority.h"
#include "PalLogAdditionalData.h"
#include "PalLogDataSet.h"
#include "PalWorldSubsystem.h"
#include "Templates/SubclassOf.h"
#include "PalLogManager.generated.h"

class UPalStaticLogCollector;
class UTexture2D;

UCLASS(Blueprintable)
class PAL_API UPalLogManager : public UPalWorldSubsystem {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemovedVeryImportantLogDelegate, const FGuid&, logId);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAddedVeryImportantLogDelegate, const FGuid&, logId, const FText&, LogText, const FPalLogAdditionalData&, logAdditionalData);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAddedNormalLogDelegate, const FText&, LogText, const FPalLogAdditionalData&, logAdditionalData);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAddedImportantLogDelegate, const FText&, LogText, const FPalLogAdditionalData&, logAdditionalData);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAddedDeathLogDelegate, const FText&, LogText, const TSoftObjectPtr<UTexture2D>, Icon);
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float normalLogDisplayTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float importantLogDisplayTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float veryImportantLogDisplayTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DeathLogShortDisplayTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DeathLogLongDisplayTime;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FGuid, FPalLogDataSet> veryImportantLogMap;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UPalStaticLogCollector> staticLogCollectorClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UPalStaticLogCollector* staticLogCollector;
    
public:
    UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FAddedNormalLogDelegate OnAddedNormalLogDelegate;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FAddedImportantLogDelegate OnAddedImportantLogDelegate;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FAddedVeryImportantLogDelegate OnAddedVeryImportantLogDelegate;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRemovedVeryImportantLogDelegate OnRemovedVeryImportantLogDelegate;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FAddedDeathLogDelegate OnAddedDeathLogDelegate;
    
    UPalLogManager();

    UFUNCTION(BlueprintCallable)
    bool RemoveVeryImportantLog(const FGuid& targetLogId);
    
    UFUNCTION(BlueprintCallable)
    FGuid AddLog(EPalLogPriority logPriority, const FText& LogText, const FPalLogAdditionalData& logAdditionalData);
    
    UFUNCTION(BlueprintCallable)
    void AddDeathLog(const FText& LogText, const TSoftObjectPtr<UTexture2D> Icon);
    
};

