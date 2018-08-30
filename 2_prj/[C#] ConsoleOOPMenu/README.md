# EzDBAccess
 Класи для простого створення консольного меню.

## Фичи
 * Робота з БД як з List<T>. Ніяких додаткових функцій.
 
## Як використовувати
```С#
//Приклад меню
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

//Приклад не меню
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

//Як це використовувати
IState startState = new AuthState();    
while(startState!=null) 
	startState = startState.RunState();
	
//Приклад з ConfigurableMenuState
var menuState = new ConfigurableMenuState();
menuState.AddMenuItem(1, new MenuItem() {Text = "Option 1"}, ()=> menuState);
menuState.AddMenuItem(2, new MenuItem() {Text = "Exit"}, ()=> null);

//Приклад з AutoConfigurableMenuState
var menuState = new ConfigurableMenuState();
menuState.AddMenuItem(new MenuItem() {Text = "Option 1"}, ()=> menuState);
menuState.AddMenuItem(new MenuItem() {Text = "Exit"}, ()=> null);
```

## API
 * **MenuItem** - Для виводу тексту в консоль. Підтримує кольори
 * **IState** - Базовий клас для всіх станів вікна.
 * **MenuState** - Базовий елас для меню
 * **ConfigurableMenuState** - Зручно додавати пункти меню через AddMenuItem()
 * **AutoConfigurableMenuState** - Як ConfigurableMenuState, але Id ставиться самостійно
	
 
## Зроблено на
 * С#