modded class MissionServer
{
	// Called when server mission initializes
	override void OnInit()
	{
		super.OnInit();

		// Dump objects / spawn chicken coops
		if (GetGame().IsDedicatedServer())
		{
			// Dump object locations
			if (GetZenChickenCoopsConfig().DumpObjectLocations)
			{
				// Wait 20 secs to ensure all vanilla + modded items are loaded in
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DumpChickenCoopObjects, 20000, false);
			}
			else
			if (GetZenChickenCoopsConfig().SpawnChickenCoops || GetZenChickenCoopsConfig().DebugOn)
			{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SetupChickenCoops, 20000, false);
			}
		}
	}

	// Sets up chicken coops across the map
	void SetupChickenCoops()
	{
		ZenChickenCoopsLogger.Log("Setting up chicken coops...");
		int minFeathers;
		int maxFeathers;
		vector objOffset;
		vector objOrient;

		foreach (ZenChickenCoopObject coop : GetZenChickenCoopsConfig().CoopPositions)
		{
			objOffset = GetZenChickenCoopsConfig().GetOffset(coop.TypeName);
			objOrient = GetZenChickenCoopsConfig().GetOrient(coop.TypeName);

			foreach (vector loc : coop.Locations)
			{
				// Get objects within 1 meter of the config'd coop vector
				array<Object> objectsNearCoop = new array<Object>;
				GetGame().GetObjectsAtPosition(loc, 1, objectsNearCoop, null);

				// Prepare reused variables
				string debugName = "";
				string className = "";

				// Check to make sure we haven't got an existing interactive coops on this location due to persistence issues if there is a types.xml entry
				foreach(Object z_obj : objectsNearCoop)
				{
					className = z_obj.ClassName();
					className.ToLower();

					if (className.Contains("zen_chickencoop"))
					{
						GetGame().ObjectDelete(z_obj);
						break;
					}
				}

				foreach (Object obj : objectsNearCoop)
				{
					// Get classname(s)
					debugName = obj.GetDebugNameNative();
					className = obj.ClassName();

					// Convert to lower
					debugName.ToLower();
					className.ToLower();

					// Skip any existing coops
					if (className.Contains("zen_chickencoop"))
					{
						continue;
					}

					// If map object is what we're looking for, attach an interactive chicken coop object to it
					if (debugName.Contains(coop.TypeName) || className.Contains(coop.TypeName))
					{
						string coopModel = GetZenChickenCoopsConfig().GetObjectName(coop.TypeName);

						if (GetZenChickenCoopsConfig().DebugOn)
							coopModel = coopModel + "_Debug";

						GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CreateZenChickenCoop, 1, false, obj, coopModel, objOffset, objOrient);
					}
				}
			}
		}

		ZenChickenCoopsLogger.Log("Done.");
	}

	// Creates an interactive object on the static chicken coops
	static void CreateZenChickenCoop(Object parentObj, string childObjType, vector offset, vector orient)
	{
		if (!parentObj)
			return;

		childObjType.ToLower();
		Object newObj = GetGame().CreateObject(childObjType, vector.Zero);
		newObj.SetPosition(parentObj.GetPosition() + offset);
		newObj.SetOrientation(parentObj.GetOrientation() + orient);
		newObj.Update();
	}

	// Dump all objects around the map that match our typenames.
	void DumpChickenCoopObjects()
	{
		ZenChickenCoopsLogger.Log("Start object dump.");

		// Get all objects on the map in a 30km radius from the center of that 30km radius (enough for most maps?)
		array<Object> objectsOnMap = new array<Object>;
		GetGame().GetObjectsAtPosition(Vector(10000, 0, 10000), 30000, objectsOnMap, null);
		int objCount = 0;

		foreach(ZenChickenCoopType coopType : GetZenChickenCoopsConfig().CoopTypes)
		{
			string type = coopType.TypeName;
			type.ToLower();

			// Prepare this object
			ZenChickenCoopObject coopObj = new ZenChickenCoopObject;
			coopObj.TypeName = type;
			array<vector> objLocations = new array<vector>;

			// Cycle through all map objects
			for (int x = 0; x < objectsOnMap.Count(); x++)
			{
				// Prepare classname(s)
				string debugName = "";
				string className = "";

				// Get classname(s)
				debugName = objectsOnMap[x].GetDebugNameNative();
				className = objectsOnMap[x].ClassName();

				// Convert to lower
				debugName.ToLower();
				className.ToLower();

				// If map object is what we're looking for, add it to the array
				if (debugName.Contains(type) || className.Contains(type))
				{
					objLocations.Insert(objectsOnMap[x].GetPosition());
					objCount++;
				}
			}

			// Save this chicken coop type & all its locations
			coopObj.Locations = objLocations;
			GetZenChickenCoopsConfig().CoopPositions.Insert(coopObj);
		}

		// Save objects and disable object dump for next restart
		ZenChickenCoopsLogger.Log("End object dump - found " + objCount + " relevant objects out of a total of " + objectsOnMap.Count() + " map objects.");
		GetZenChickenCoopsConfig().DumpObjectLocations = false;
		GetZenChickenCoopsConfig().Save();

		// Clear array & delete from memory
		objectsOnMap.Clear();
		objectsOnMap = NULL;

		// Setup chicken coops
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SetupChickenCoops, 5000, false);
	}
}