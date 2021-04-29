// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/Nodes/TesBPGraphK2Node_Base.h"


UTesBPGraphK2Node_Base::UTesBPGraphK2Node_Base()
{}


UEdGraphPin* UTesBPGraphK2Node_Base::GetInputPin() const
{
	if (Pins.Num() == 0 || Pins[0]->Direction == EGPD_Output)
	{
		return nullptr;
	}

	return Pins[0];
}


UEdGraphPin* UTesBPGraphK2Node_Base::GetOutputPin() const
{
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->Direction == EGPD_Output)
		{
			return Pin;
		}
	}

	return nullptr;
}


UEdGraphPin* UTesBPGraphK2Node_Base::GetThenPin() const
{
	UEdGraphPin* Pin = FindPinChecked(UEdGraphSchema_K2::PN_Then);
	if (Pin->Direction == EGPD_Output)
	{
		return Pin;
	}

	return nullptr;
}


UEdGraphNode* UTesBPGraphK2Node_Base::GetOutputNode() const
{
	UEdGraphPin* OutputPin = GetOutputPin();

	if (OutputPin)
	{
		check(OutputPin->LinkedTo.Num() <= 1);
		if (OutputPin->LinkedTo.Num() > 0 && OutputPin->LinkedTo[0]->GetOwningNode() != nullptr)
		{
			return OutputPin->LinkedTo[0]->GetOwningNode();
		}
	}

	return nullptr;
}