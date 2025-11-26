# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
# Le flag -Iinclude indique au compilateur de chercher les fichiers d'en-tête dans le dossier 'include'

# Dossiers
OBJ_DIR = obj
BIN_DIR = bin

# Détection automatique des sources
# On cherche tous les .c dans les sous-dossiers respectifs
SRCS_SERVER = $(wildcard src/server/*.c)
SRCS_CLIENT = $(wildcard src/client/*.c)
SRCS_COMMON = $(wildcard src/common/*.c)

# Génération des noms d'objets (.o)
# On ajoute un préfixe (server_ ou client_) pour éviter les conflits (ex: main.o)
OBJS_SERVER = $(patsubst src/server/%.c, $(OBJ_DIR)/server_%.o, $(SRCS_SERVER))
OBJS_CLIENT = $(patsubst src/client/%.c, $(OBJ_DIR)/client_%.o, $(SRCS_CLIENT))
OBJS_COMMON = $(patsubst src/common/%.c, $(OBJ_DIR)/common_%.o, $(SRCS_COMMON))

# Cible par défaut : tout construire
all: create_dirs server client

# --- Linkage (Création des exécutables) ---

# Le Serveur a besoin de ses objets + les objets communs
server: $(OBJS_SERVER) $(OBJS_COMMON)
	@echo "Construction du Serveur..."
	$(CC) $(CFLAGS) -o $(BIN_DIR)/Server $^

# Le Client a besoin de ses objets + les objets communs
client: $(OBJS_CLIENT) $(OBJS_COMMON)
	@echo "Construction du Client..."
	$(CC) $(CFLAGS) -o $(BIN_DIR)/Client $^

# --- Compilation (Création des .o) ---

# Règle pour compiler les sources du Serveur
$(OBJ_DIR)/server_%.o: src/server/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour compiler les sources du Client
$(OBJ_DIR)/client_%.o: src/client/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour compiler les sources Communes
$(OBJ_DIR)/common_%.o: src/common/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Utilitaires ---

# Crée les dossiers bin et obj s'ils n'existent pas
create_dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Nettoyage complet
clean:
	@echo "Nettoyage..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean create_dirs   