
# ☕ Java OOP Projects Collection

This repository showcases four Java Object-Oriented Programming (OOP) mini-projects, each focusing on a different OOP design principle or pattern. These projects include practical implementations of **Template Method**, **Custom Interface with Utility**, **Command Pattern**, and **Decorator Pattern**.

---

## 📂 Project 1 – Beverage Template Method

### 🧠 Pattern: Template Method

Implements a fixed drink-making procedure using an abstract class `BeverageMaker` and allows subclasses to define custom steps (e.g., `brew()` and `addCondiments()`).

### 🔧 Key Classes
- `BeverageMaker`: Abstract class with `prepare()` method (final)
- `CoffeeMaker`, `TeaMaker`: Concrete implementations
- `Test`: Executes both drink makers

### 💡 Highlights
- Fixed sequence defined in `prepare()`
- Common logic reused (`boilWater`, `pourInCup`)
- Subclasses customize behavior via abstract methods

### 📌 Example Output
```
Boiling water...
Brewing coffee...
Pouring into cup...
Adding sugar and milk...
Adding ice...
------------------
Boiling water...
Steeping tea...
Pouring into cup...
Adding lemon...
```

---

## 📂 Project 2 – Custom Sorting System

### 🧠 Concept: Interface + Utility Class

Defines a `Compare` interface and a sorting method `mySort()` in `MyUtility` that checks for interface compliance at runtime.

### 🔧 Key Classes
- `Compare`: Interface with `compare()` method
- `Work`: Implements `Compare` with custom string sorting
- `MyUtility`: Contains `mySort(Object[])` method
- `Test`: Demonstrates sorting logic

### 💡 Highlights
- Uses `instanceof` and casting to enable generic sorting
- Sort logic defined in user class (`Work`)
- Extensible to other comparable types

### 📌 Example Output
```
Before sorting:
Delta
Alpha
Charlie
Bravo

After sorting:
Alpha
Bravo
Charlie
Delta
```

---

## 📂 Project 3 – Smart Remote Control

### 🧠 Pattern: Command Pattern

Implements a remote control system that decouples command execution from device logic using the Command pattern.

### 🔧 Key Classes
- `Command`: Interface with `execute()` method
- `ControlTV`, `ControlLight`, `ControlSoundbox`: Device controllers
- `Television`, `Light`, `Soundbox`: Real device logic
- `Remote`: Assigns buttons to `Command`
- `TestRemote`: Sets up and tests the remote

### 💡 Highlights
- Remote logic unaware of device types
- Easy to extend to new appliances
- Flexible button-to-command mapping

### 📌 Example Output
```
TV is turned ON
Soundbox volume increased
Light is now OFF
TV is turned OFF
```

---

## 📂 Project 4 – Beverage Decorator

### 🧠 Pattern: Decorator Pattern

Implements dynamic ingredient composition using a base class `Beverage`. Each topping or drink is a subclass that wraps the previous one.

### 🗂 UML Overview
![UML Diagram](./UML.jpg)

### 🔧 Key Classes
- `Beverage`: Abstract base with `getIngredient()` and `getCost()`
- `BlackTea`, `GreenTea`: Base drinks
- `Milk`, `Pearl`, `Suger`: Toppings
- `TestBeverage`: Builds and prints layered drinks

### 💡 Highlights
- Layered ingredient chaining via constructors
- Recursive description and cost calculation
- New toppings added easily by extending `Beverage`

### 📌 Example
```java
Beverage drink = new Suger(new Pearl(new BlackTea()));
System.out.println(drink.getIngredient());
System.out.println("Total cost: " + drink.getCost());
```

**Output:**
```
紅茶 + 珍珠 + 糖
Total cost: 35
```

---

## 👨‍💻Conclusion

This multi-project compilation demonstrates the use of **OOP principles and design patterns** in practical Java programs, with a focus on modularity, abstraction, and code reusability.

---
