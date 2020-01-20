class enable_disable_layers : trigger_base
{
	script@ script;
	scripttrigger@ self;
	scene@ g;
	[checkbox] array<bool>layer_array(21,true);
	[hidden] bool active = false;
	array<string> types = {"dust_girl","dust_worth","dust_man","dust_kid"};
	
	enable_disable_layers()
	{
		@g = get_scene();
	}
	
	void init(script@ s, scripttrigger@ self)
	{
		@this.script = @s;
		@this.self = @self;
	}
	
	void activate(controllable@ e)
	{
		if(!check_char(e.as_entity()))
			return;
		if(!active)
		{
			active = true;
			for(int i = 0;i < 21;i++)
			{
				g.layer_visible(i,layer_array[i]);
			}
			g.remove_entity(@self.as_entity());
		}
	}
	
	bool check_char(entity@ e)
	{
		string type = e.type_name();
		for(int i = 0;i < 4;i++)
		{
			if(type == types[i])
				return true;
		}
		return false;
	}
}