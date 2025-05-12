---

# 42.Philosophers

![Philo](https://github.com/user-attachments/assets/12c756f8-48a1-4375-99f5-26215e1311c1)

---

## 🇫🇷 Philosopher - Projet 42

### Description

Le projet "Philosopher" fait partie du cursus de 42. Il a pour but d'implémenter une solution au problème classique de synchronisation des philosophes mangeurs. Ce projet vous apprend à travailler avec les threads, les mutex et la gestion des ressources partagées.

### Fonctionnalités

- Simulation de philosophes autour d'une table avec des fourchettes.
- Synchronisation pour éviter les conditions de famine et les blocages.
- Gestion des threads et ressources en C.

---

### Guide d'utilisation

1. **Cloner le dépôt :**
   ```bash
   git clone https://github.com/LolelsayFR/42.Philosophers.git
   cd 42.Philosophers/philo
   ```

2. **Compiler le programme :**
   Utilisez le `Makefile` fourni pour compiler le projet :
   - `make` : Compile le programme.
   - `make clean` : Supprime les fichiers objets.
   - `make fclean` : Supprime les fichiers objets et l'exécutable.
   - `make re` : Nettoie et recompile tout.

3. **Exécuter le programme :**
   ```bash
   ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
   ```

   - **Arguments :**
     - `<number_of_philosophers>` : Nombre de philosophes et de fourchettes.
     - `<time_to_die>` : Temps en millisecondes avant qu'un philosophe meure s'il ne mange pas.
     - `<time_to_eat>` : Temps en millisecondes qu'un philosophe met pour manger.
     - `<time_to_sleep>` : Temps en millisecondes qu'un philosophe met pour dormir.
     - `[number_of_times_each_philosopher_must_eat]` (optionnel) : Nombre minimal de repas pour chaque philosophe.

4. **Exemple :**
   ```bash
   ./philo 5 800 200 200
   ```

---

## 🇬🇧 Philosopher - 42 Project

### Description

The "Philosopher" project is part of the 42 curriculum. Its goal is to implement a solution to the classic synchronization problem known as the "Dining Philosophers Problem". This project teaches you how to work with threads, mutexes, and shared resource management.

### Features

- Simulation of philosophers around a table with forks.
- Synchronization to avoid starvation and deadlocks.
- Thread and resource management in C.

---

### Usage Guide

1. **Clone the repository:**
   ```bash
   git clone https://github.com/LolelsayFR/42.Philosophers.git
   cd 42.Philosophers/philo
   ```

2. **Compile the program:**
   Use the provided `Makefile` to compile the project:
   - `make` : Compile the program.
   - `make clean` : Remove object files.
   - `make fclean` : Remove object files and the executable.
   - `make re` : Clean and recompile everything.

3. **Run the program:**
   ```bash
   ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
   ```

   - **Arguments:**
     - `<number_of_philosophers>` : Number of philosophers and forks.
     - `<time_to_die>` : Time in milliseconds before a philosopher dies if they do not eat.
     - `<time_to_eat>` : Time in milliseconds it takes a philosopher to eat.
     - `<time_to_sleep>` : Time in milliseconds it takes a philosopher to sleep.
     - `[number_of_times_each_philosopher_must_eat]` (optional) : Minimum number of meals each philosopher must eat.

4. **Example:**
   ```bash
   ./philo 5 800 200 200
   ```

---