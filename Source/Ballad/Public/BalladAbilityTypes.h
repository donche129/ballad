#pragma once

#include "GameplayEffectTypes.h"
#include "BalladAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FBalladGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsCriticalHit() const { return bIsCriticalHit; }

	void SetIsBlockedHit(bool InIsBlockedHit) { bIsBlockedHit = InIsBlockedHit; }
	void SetIsCriticalHit(bool InIsCriticalHit) { bIsCriticalHit = InIsCriticalHit; }

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FBalladGameplayEffectContext* Duplicate() const
	{
		FBalladGameplayEffectContext* NewContext = new FBalladGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
	
protected:

	UPROPERTY()
	bool bIsBlockedHit = false;
	
	UPROPERTY()
	bool bIsCriticalHit = false;
	
};

template<>
struct TStructOpsTypeTraits<FBalladGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FBalladGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};
