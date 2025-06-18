# TermiDo — Terminal Productivity Tool in C

A simple C program that combines a:
- 📝 To-Do List Manager (in memory + encrypted file)
- 🔐 File Encryptor using XOR password protection
- 💻 Basic Custom Shell using fork + exec

Built to relearn and master the C programming language from scratch.

## Features
- Add tasks with descriptions
- List all tasks with completion status
- Mark tasks as done
- Delete tasks by index
- Save tasks to an encrypted file (`tasks.enc`)
- Load tasks on startup with automatic decryption
- CLI-style terminal interface

## Project Structure

```bash
termido/
├── include/ # Header files (interfaces)
│ ├── todo.h
│ └── crypto.h
├── src/ # Source code (implementations)
│ ├── main.c # CLI interface
│ ├── todo.c # Task logic (add, list, delete, etc.)
│ └── crypto.c # XOR encryption logic
├── build/ # Compiled object files (.o)
│ └── *.o
├── tasks.enc # Encrypted saved task file
├── Makefile # Build instructions
├── README.md # Project documentation
└── .gitignore # Excludes build files and encrypted output
```

> Built to be modular and scalable like a real C production app.

## Build & Run

```bash
make
./termido
```

## Commands

```bash
add [task]       - Add a new task
list             - View all tasks
done [index]     - Mark a task as completed
remove [index]   - Delete a task
help             - View commands
exit             - Save and exit
```

## File Storage

- Tasks are saved to `tasks.enc` on exit.
- The file is encrypted using a basic XOR cipher.
- Decrypted automatically when the app starts.

## Encryption Info
- XOR encryption with a hardcoded key: `"supersecret"`
- (Future plan: let user input their own key at runtime)

## Style
🧠 Git Commit Strategy: I follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) spec to ensure clean versioning, maintainability, and compatibility with automated tooling.

## Screenshots

- Will be added in the future

## Author

👨‍💻 Samii Shabuse  
🔗 [LinkedIn Profile](https://www.linkedin.com/in/samiishabuse/)
