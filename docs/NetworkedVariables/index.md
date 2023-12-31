# Networked Variables

A wrapper for serialization of variables that are to be transmitted over the network stack. 

## Registering Variables

Variables are registered using the `Register` method. Pass in the name of the variable for the first parameter. Variables within variables can also be registered, delimited by a period (`.`) with a maximum depth of 3. Do not register a variable of `Class` type as that will result in a error. Instead make use of individually registering variables.

## Sending and Recieving Changes

Using `ScriptRPC`, call `Write` on sending the RPC and `Read` on recieving the RPC.

## Custom Types

Register a [Type Converter](../TypeConverters/index.md) to create a custom variable type that can be synchronized. Make sure to override the `Read(Serializer)` and `Write(Serializer)` methods so only your custom fields are sent, and not the class. Make sure to not set Class types to be synchronized as that will have undefined side effects.

## Example

this just an example for arkensor, actual docs later

```csharp
class DataClass
{
	float m_SomeVariable;
};

class SomeClass
{
	const static int RPC_ID = 1000000;

	private ref DataClass m_DataHolder = new DataClass();
	private int m_SomeIntVariable;

	private ref CF_NetworkedVariables m_NetworkVariables = new CF_NetworkedVariables(this);

	void SomeClass()
	{
		GetDayZGame().Event_OnRPC.Insert(OnRPC);

		m_NetworkVariables.Register("m_SomeIntVariable");
		m_NetworkVariables.Register("m_DataHolder.m_SomeVariable");
	}

	void OnVariablesSynchronized()
	{
		Print(m_SomeIntVariable);
		Print(m_DataHolder.m_SomeVariable);
	}

	void SetSynchDirty()
	{
		ScriptRPC ctx = new ScriptRPC();
		m_NetworkVariables.Write(ctx);
		ctx.Send(null, RPC_ID, true, null);
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (id != RPC_ID) return;
		m_NetworkVariables.Read(ctx);
		OnVariablesSynchronized();
	}
	
	void SetSomeClassFloatVariable(float newFloat)
	{
		m_DataHolder.m_SomeVariable = newFloat;

		SetSynchDirty();
	}
	
	void SetSomeIntVariable(int newNum)
	{
		m_SomeIntVariable = newNum;

		SetSynchDirty();
	}
};
```
