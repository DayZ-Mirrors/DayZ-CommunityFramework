
static bool ShowedTutorialMessage;

// Check JM/CF/GUI/layouts/sample_mvc.layout
class SampleController: Controller
{	
	// Properties
	float slider_value = 25; // default value will be 25
	float progress_value = 75; // default value will be 75
	
	void SampleController()
	{
		// This is just to get you into this file. Ignore it :)
		if (!ShowedTutorialMessage)
			Workbench.Dialog("Welcome to MVC!", "Check \"SampleController\" class for an example on how to use this utility!");
		
		ShowedTutorialMessage = true;
	}
	
	override void PropertyChanged(string property_name)
	{
		switch (property_name) {
			
			case "slider_value": {
				
				// sets progress_value to any value you want
				progress_value = Math.AbsFloat(slider_value - 100); 
				
				// MUST be called when changing a property, notifies the UI that something changed!
				NotifyPropertyChanged("progress_value"); 
				break;
			}
		}
	}
}

class SampleSubController: Controller
{
	bool button_state = true;
	
	// Dont use FindAnyWidget - Enfusion will automatically asign it if its the same name as the Widget name
	ButtonWidget button; 
	
	int observable_combo_selection;
	ref ObservableCollection<string> observable_combo_box = new ObservableCollection<string>("observable_combo_box", this);
	

	static const int COLOR_ON = COLOR_GREEN;
	static const int COLOR_OFF = COLOR_RED;
	
	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		
		observable_combo_box.Insert("Item1");
		observable_combo_box.Insert("Item2");
		observable_combo_box.Insert("Item3");
	}
	
	override void PropertyChanged(string property_name)
	{
		switch (property_name) {
			
			case "button_state": {
				if (button_state) {
					button.SetColor(COLOR_ON);
				} else {
					button.SetColor(COLOR_OFF);
				}
				
				break;
			}
			
			case "observable_combo_selection": {
				Print("Combo Box Selection = " + observable_combo_box.Get(observable_combo_selection));
				break;
			}
		}
	}
}