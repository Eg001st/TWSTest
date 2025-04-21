# Cable Pole Spawner System (Unreal Engine)

## Overview

This project implements a tool for automatically placing poles and connecting them with cables using Unreal Engine. The system is modular, editable in-editor, and designed with level designers in mind. It offers a flexible setup with realistic cable behavior and easy-to-use Blueprint classes.
![image](https://github.com/user-attachments/assets/61733267-32b7-47ef-b577-803bf8cd008d)

---

## Project Structure

### `ATWSCableActor` – Cable Actor

- Contains a `UCableComponent` which simulates cable physics.
- Manual connection between cables and poles was removed due to instability during construction and play modes.
- Cables are automatically stretched between sockets on poles.

### `ATWSBasePole` – Base Pole Class

- Defines poles that can have a configurable number of cable pairs (`NumCablePairs`).
- Allows support for single or multi-line connections.

### `APoleSpawner` – Pole Spline Spawner

- Spawns poles along a spline based on a given `DistanceBetweenPoles`.
- Contains two `CallInEditor` methods:
  - `RebuildPolesAndLines`: Creates a visual preview of poles and cables in the editor.
  - `ClearPolesAndLines`: Clears preview actors before runtime to prevent duplication.

![image](https://github.com/user-attachments/assets/35ef7981-3dfd-4069-9298-fbec8a58bdd4)

> **⚠️ Warning**  
> If you use `RebuildPolesAndLines` to visualize poles and cables in the editor,  
> you **must** run `ClearPolesAndLines` before entering Play Mode.  
> Failing to do so will result in duplicated actors, broken cable connections, and other unexpected behavior.
---

## Why Use `CableComponent`

- **Built-in physics**: Supports gravity, tension, flexibility, and dynamic behavior.
- **Easy attachment**: Can be connected to specific sockets on components.
- **Visual fidelity**: Looks natural without requiring custom logic or shaders.

---

## Separation into Independent Classes

This approach follows the Single Responsibility Principle:

- `ATWSCableActor`: Handles cable simulation and visuals.
- `ATWSBasePole`: Contains all pole-specific properties and logic.
- `APoleSpawner`: Manages generation and linking along a spline.

**Benefits:**

- Improves modularity and code reuse.
- Enables designers to work independently in Blueprints.
- Makes the system easier to test and extend.

---

## Why Use Sockets for Cable Connections

- Allows precise control over attachment points on the mesh.
- Supports multiple cable lines per pole.
- Ensures consistent alignment regardless of mesh orientation.
- Sockets are fully compatible with `CableComponent` attachment.

![image](https://github.com/user-attachments/assets/03c5b65f-8bc6-40e8-a2da-658fadbcd34f)

---

## Alternative Considered: Spline + Instanced Static Mesh

**Pros:**

- Efficient for rendering (Instanced Static Meshes).
- Simple to implement for straight lines or non-physical cables.

**Why it was not used:**

- No built-in physics or cable sag simulation.
- Requires complex math to replicate physical behavior.
- Difficult to attach to sockets and simulate natural cable behavior.

---

## Possible Improvements

- **Object Pooling**:
  - Reduce runtime and editor overhead by reusing pole and cable actors.

- **Automatic Rebuilding**:
  - Use `PostEditChangeProperty` to rebuild actors when properties are modified.

- **Better UX for Designers**:
  - Add socket selectors and previews in the Details panel.

- **Data-driven Configuration**:
  - Support saving and loading pole/cable setups using Data Assets or external configs.

---

## Conclusion

The result is a modular and physics-based system for cable-pole simulation in Unreal Engine 5. It prioritizes visual realism and ease of use, while remaining flexible for future extension and optimization.

