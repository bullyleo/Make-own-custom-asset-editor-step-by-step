// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TesBPGraphK2Node_Base.h"
#include "TesBPGraphK2Node_Base.generated.h"

/**
 * 自作ノードすべての基底クラス.
 * このノード(または継承したノード)はあくまでも見た目だけのものであり、具体的な処理は実装されない.
 * これはUEdGraphNodeやUK2Nodeも同様.
 * 
 * もしグラフノードに具体的な処理をさせたい場合
 * 具体的な処理(「Hello World」とログに表示する等)は別途BlueprintFunctionLibraryに実装しておき
 * ExpandNode関数オーバーライド時にFunctionLibraryに定義した関数をこのノードと紐付ける.
 * 参考: https://neil3d.gitee.io/unreal/custom_bp_node.html
 */
UCLASS()
class UTesBPGraphK2Node_Base : public UK2Node
{
	GENERATED_BODY()

public:
	UTesBPGraphK2Node_Base();

	// ユーティリティ.
	virtual UEdGraphPin* GetInputPin() const;
	virtual UEdGraphPin* GetOutputPin() const;
	virtual UEdGraphPin* GetThenPin() const;
	virtual UEdGraphNode* GetOutputNode() const;
	// ~ユーティリティ.
};
