What Is This?

This mod adds the ability to harvest feathers from chicken coops (used for crafting crossbow bolts).

It's based on my Firewood mod that allows players to harvest firewood from firewood piles, pretty much copy & pasted that mod and adapted the classnames to work with chicken coops.

There is a JSON config that allows you to specify what objects count as chicken coops and how many feathers can be harvested from each (feather quantity resets on server restarts).

How It Works (For Server Owners):

The mod spawns invisible objects on every chicken coop on the map based on the objects you define in the json config. 

By default the mod will automatically detect the static object types that contain these words in their classname: _chickencoop, _hutch

It works with the vanilla static objects and any bldr_ objects placed with the DayZ Editor or spawned in with the json/init.c/etc methods.

This means you can place chicken coops on Namalsk for example, and players can harvest feathers from them.

The technique used in this mod to automatically detect static objects can be used to detect and interact with almost any other object in the game, such as creating dynamic street lighting (a separate mod I will release in the future).

So check out the source code if you're wanting to add dynamic interactions to other static objects other than fire wood piles and chicken coops.

Installation Instructions:

Install this mod like any other mod - copy it into your server folder and add it to your mods list. Make sure to copy the .bikey into your server keys if you're not using a server management tool like OmegaManager which does that automatically.

When you run the mod for the first time a default JSON config will be created in your server profile: %server_root%/profiles/Zenarchist/ZenChickenCoopsConfig.json

This mod must be installed on both the server & client.

Repack & Source Code:

You can repack this mod if you like, and do anything else you want with it for that matter. The source code is on my GitHub at www.zenarchist.io

Enjoy!
