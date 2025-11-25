# virtualHomeDir


2026-winter-project/
├── Makefile               # Script de compilation automatique 
├── README.md              # Documentation (compilation, exécution, commandes)
├── .gitignore             # Pour ignorer les binaires et fichiers objets (.o)
├── bin/                   # Dossier pour les exécutables finaux (Server, Client)
├── obj/                   # Dossier pour les fichiers objets intermédiaires (.o)
├── include/               # Tous les fichiers d'en-tête (.h) - Les contrats
│   ├── common.h           # Macros partagées (MAX_BUFFER, codes erreurs)
│   ├── network.h          # Prototypes gestion sockets
│   ├── protocol.h         # Structures des messages (Command struct)
│   ├── session.h          # Gestion auth et utilisateurs
│   ├── fs_utils.h         # Opérations fichiers et Sandboxing
│   └── transfer.h         # Logique d'envoi/réception de fichiers
├── src/                   # Tous les fichiers sources (.c) - L'implémentation
│   ├── common/            # Code partagé entre Client et Serveur
│   │   ├── network.c      # socket(), bind(), accept(), send_all(), recv_all()
│   │   ├── protocol.c     # Sérialisation/Désérialisation des commandes
│   │   └── utils.c        # Fonctions helpers (logging, string parsing)
│   ├── server/            # Logique spécifique au Serveur
│   │   ├── main.c         # Point d'entrée (argc/argv parsing, boucle accept)
│   │   ├── session.c      # Login, create_user (exec sudo adduser)
│   │   ├── fs_manager.c   # Logique list, delete, path resolution (Sandbox)
│   │   └── worker.c       # Gestion du processus enfant par client
│   └── client/            # Logique spécifique au Client
│       ├── main.c         # Point d'entrée, boucle de commandes
│       ├── parser.c       # Traduit "read -offset=10" en structure Protocol
│       └── async.c        # Gestion des fork() pour upload/download -b