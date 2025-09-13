# Gameplay Action System (Demo)

This project demonstrates a **gameplay action architecture**, built on top of an object manager and slot-based container.  
The goal is to show how game objects (Entities) can own and manage actions through a unified interface.

---

## 📐 UML Diagram

![UML Diagram](https://www.plantuml.com/plantuml/png/XLJDRXCn4BxxAKOzb4qWYNgDegW1fO14gO305JcxawofOwVsB11H3bouSaV7Y1e48X8_l8BxHdZjZTXi8hXaFT_CVDzdE-DZlznGiP2C14c4to1lybNS3PzWldrHYa9hM1aqboG1mg3aCmAALkcfP9R2q-afbEdC0R1d1JA8k6aax1NsunrKiOJHS8j9ZlCL6jPudEa6ZffbzXCc-V8qpmvKltjSfA9VhoGudCqbTXZd0jD89B9OQkCdohJ4qw6KUg4DxXKewaJ4wHSftTWcwtMvCOAnAqjYlZ8jR7qpVTwW4XxZOfBGRwoDl6JjiiLiv7p85nWQBHCXvj6GketFX1LJYsb57y9lID_ug42pgXL_l-3Mc1M7lCDmm49N-pVWlKz9cKEzk3sidlKLGJgfueDFfpFKZFjy3xoYuzJuMn6-0-kQlhT-wx--g-k5J_kixjoFZtw-WFRvxBJKhmshdln3WQNdKoTMvuoMgtODVXH-l_hX_lJvxzP-_LTsgshFZWuEe2sRogJ_UmplbBMtozSzNaBDPZ00KveGZG7d17hs5uTgG3fJR6Z3L2lyGG7f-unl9pwL20Pd052bQ0DwbXor80vPBmmLGvL1AT2KsRSBy8Uen5aOMRqe...longlink...)

---

## ⚙️ Core Components

- **Entity** – Game object that owns a set of actions  
- **EntityAction** – Base class for all actions (name, visibility, execution)  
- **EntityActionManager** – Manages registration and visibility of actions  
- **ObjectManager<T>** – Generic manager with iteration & bulk calls  
- **SlotMap<T>** – Handle-based container with stable references and O(1) insert/erase  

---

## 🛠 Example Actions

- `OpenAction` — Open an object  
- `LockpickAction` — Pick a lock  
- `InspectAction` — Inspect an object  

---

## ✅ Testing

Unit tests are implemented with **GoogleTest** in `Bohemia_Tests/EntityActionTests.cpp`.

---

## 🚀 Build & Run

```bash
git clone https://github.com/SpaceOak/Demos.git
