# ConsoleOOPMenu
 Librrary for console menu and UI

## How 2 use
```С#
//Menu example
public class MenuState1 : MenuState
{
    private Dictionary<int, MenuItem> _menus = new Dictionary<int, MenuItem>() {
        {1, new MenuItem(){Text = "Menu 1"}},
        {2, new MenuItem(){Text = "Menu 2"}},
        {3, new MenuItem(){Text = "Menu 3"}},
        {4, new MenuItem(){Text = "Exit"}},
    };
    protected override Dictionary<int, MenuItem> Menus => _menus;

    protected override IState NextState(KeyValuePair<int, MenuItem> selectedMenu)
    {
        if (selectedMenu.Key == 4) return null;
        if (selectedMenu.Key == 1) return new AuthState();
        return this;
    }
}

//Not menu example
public class AuthState : IState
{   
    public IState RunState()
    {
        Console.WriteLine("Login: ");
        var login = Console.ReadLine();
        Console.WriteLine("Password: ");
        var password = Console.ReadLine();

        Console.WriteLine($"Hello, {login}");

        return new MenuState1();
    }
}

//How invoke new UI
IState startState = new AuthState();    
while(startState!=null) 
	startState = startState.RunState();
	
//ConfigurableMenuState example
var menuState = new ConfigurableMenuState();
menuState.AddMenuItem(1, new MenuItem() {Text = "Option 1"}, ()=> menuState);
menuState.AddMenuItem(2, new MenuItem() {Text = "Exit"}, ()=> null);

//AutoConfigurableMenuState example
var menuState = new ConfigurableMenuState();
menuState.AddMenuItem(new MenuItem() {Text = "Option 1"}, ()=> menuState);
menuState.AddMenuItem(new MenuItem() {Text = "Exit"}, ()=> null);
```

## API
 * **MenuItem** - For output text in console. Works with colors
 * **IState** - Base class for every window state
 * **MenuState** - Base class for emenu
 * **ConfigurableMenuState** - Class for eazy menus. Use AddMenuItem()
 * **AutoConfigurableMenuState** - Like ConfigurableMenuState, but Id sets auto
	
 
## Made with
 * С#
