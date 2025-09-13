\# Gameplay Action System (Demo)



This project demonstrates a \*\*gameplay action architecture\*\*, built on top of an object manager and slot-based container.  

The main goal is to show how game objects (Entities) can own and manage actions through a unified interface.



---



\## 📐 UML Diagram



!\[UML Diagram](https://www.plantuml.com/plantuml/png/XLJDRXCn4BxxAKOzb4qWYNgDegW1fO14gO305JcxawofOwVsB11H3bouSaVY7Ie48X8\_l8BxHdZjZTXi8hXaFT\_CVDzdE-DZIznGiP2C14c4kto1IybNS3PzWIdrHYa9hM1aqboG1mg3aCmAALkCfP9R2q-afbE-dC0R1d1JA8k6aacx1NsunrKciOJHS8j9ZClCL6jPudEa6ZffbzXCc-V8qpmvKItsjfA9VhoGudCqbTXZd0jBQ9B9OQkCdohJG4wq6KUg4DxXKewaJ4wHSftTWcwtMvCOAnAqYjIZB8jR7qpYTvW4XXZOfBGRwoDI6JjiiiLiv7p85nWQBHcXvj6GketFX1LJYSb57y9IID\_ug42pgX\_L-3Mc1M7ICDmm49N-pVWIKz9cKEzk3sidlKGLqGfueDFpfKZFjy3xoYuzJuMn6-0-kQlhT-wx--g-k5\_kixjoFztw-WFRvxBJkHmshdIh3WQNdKxToMwouMgtODVXH-\_hX\_ljVxzvP-\_TsgshFZWuEe2sRog\_UmplbBMtozZsNaBDPZ0OKveGZ9Zd17hs5uTgG3fJRZ63L2lYGg7f-unl9pwL20PdQ52bQ0DwbXor80vPBmmLGvL1AT2KsRSBy8UIen5aOMRqed43GM0pKxPNABDP0myqmKBj7mKNXIT3-nyF3CAp0Zge0UNS9r-fEYjNcSTH65X4CpNAOxyi7wW\_)



---



\## ⚙️ Core Components



\- \*\*Entity\*\*  

&nbsp; Game object that owns a set of actions.  



\- \*\*EntityAction\*\*  

&nbsp; Base class for all actions. Provides:  

&nbsp; - `Name()` — returns action name  

&nbsp; - `CanBeVisible()` — determines whether the action is currently valid/visible  

&nbsp; - `Execute()` — performs the action  



\- \*\*EntityActionManager\*\*  

&nbsp; Manages actions: registration, removal, visibility filtering.  

&nbsp; Inherits from `ObjectManager<EntityAction>`.  



\- \*\*ObjectManager<T>\*\*  

&nbsp; Generic manager of objects with iteration and bulk method calls.  



\- \*\*SlotMap<T>\*\*  

&nbsp; Handle-based container:

&nbsp; - Stable references  

&nbsp; - O(1) insert/erase operations  



---



\## 🛠 Example Actions



The project implements several example actions:  

\- `OpenAction` — open an object  

\- `LockpickAction` — lockpicking  

\- `InspectAction` — inspect  



---



\## ✅ Testing



Unit tests are provided with \*\*GoogleTest\*\*.  

Examples can be found in `Bohemia\_Tests/EntityActionTests.cpp`.



---



\## 🚀 Build \& Run



1\. Clone the repository:

&nbsp;  ```bash

&nbsp;  git clone https://github.com/SpaceOak/Demos.git



