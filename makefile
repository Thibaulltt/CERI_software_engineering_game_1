# Variables :

IO=archives/io.a
CARTE=archives/carte.a
ENTITE=archives/entite.a
MONSTRE=archives/monstre.a
FONCTIONS=archives/fonctionsjeu.a
COMPETENCE=archives/competence.a
PERSONNAGE=archives/personnage.a
OIO=objects/io.o
OCARTE=objects/carte.o
OENTITE=objects/entite.o
OMONSTRE=objects/monstre.o
OFONCTIONS=objects/fonctionsjeu.o
OCOMPETENCE=objects/competence.o
OPERSONNAGE=objects/personnage.o
ALL=$(IO) $(CARTE) $(ENTITE) $(MONSTRE) $(FONCTIONS) $(COMPETENCE) $(PERSONNAGE)
OALL=$(OIO) $(OCARTE) $(OENTITE) $(OMONSTRE) $(OFONCTIONS) $(OCOMPETENCE) $(OPERSONNAGE)

# Cibles que l'on peut compiler directement :
all:
	#@make -s ca	# Carte
	#@make -s co	# Compétences
	#@make -s mo	# Monstre
	#@make -s pe	# Personnage
	#@make -s en	# Entite
	#@make -s fj	# Fonctions jeu
	#@make -s io	# IO
	@make -s main.exe
ca:
	@make archives/carte.a
en:
	@make archives/entite.a
mo:
	@make archives/monstre.a
co:
	@make archives/competence.a
pe:
	@make archives/personnage.a
fj:
	@make archives/fonctionsjeu.a
	@make fonctionsjeu.exe
io:
	@make archives/io.a
doc:
	@cd documentation; doxygen documentation > doxygen_output.txt; cd latex; make;
main.exe: tests/main.cpp ca mo pe en co fj io
	@g++ $< $(OALL) -o $@ -std=c++11

# Archives des classes :

archives/io.a: objects/io.o
	@echo "Archiving $@ ..."
	@ar rvs $@ $<
archives/carte.a: objects/carte.o
	@echo "Archiving $@ ..."
	@ar rvs $@ $<
archives/entite.a: objects/entite.o
	@echo "Archiving $@ ..."
	@ar rvs $@ $<
archives/monstre.a: objects/monstre.o
	@echo "Archiving $@ ..."
	@ar rvs $@ $<
archives/competence.a: objects/competence.o
	@echo "Archiving $@ ..."
	@ar rvs $@ $<
archives/personnage.a: objects/personnage.o
	@echo "Archiving $@ ..."
	@ar rvs $@ $<
archives/fonctionsjeu.a: objects/fonctionsjeu.o
	@echo "Archiving $@ ..."
	@ar rvs $@ $<

# Objets des classes :

objects/io.o: sources/io.cpp
	@echo "Compiling $@ ..."
	@g++ -c $< -o $@ -std=c++11
objects/carte.o: sources/carte.cpp
	@echo "Compiling $@ ..."
	@g++ -c $< -o $@ -std=c++11
objects/entite.o: sources/entite.cpp
	@echo "Compiling $@ ..."
	@g++ -c $< -o $@ -std=c++11
objects/monstre.o: sources/monstre.cpp
	@echo "Compiling $@ ..."
	@g++ -c $< -o $@ -std=c++11
objects/competence.o: sources/competence.cpp
	@echo "Compiling $@ ..."
	@g++ -c $< -o $@ -std=c++11
objects/personnage.o: sources/personnage.cpp
	@echo "Compiling $@ ..."
	@g++ -c $< -o $@ -std=c++11
objects/fonctionsjeu.o:	sources/fonctionsjeu.cpp
	@echo "Compiling $@ ..."
	@g++ -c $< -o $@ -std=c++11

# Objets (main) de test des classes :

objects/io_main.o: tests/io_main.cpp
	@echo "Compiling $@ ..."
	@g++ -c $< -o $@ -std=c++11
objects/fonctionsjeu_main.o: tests/fonctionsjeu_main.cpp
	@echo "Compiling $@ ..."
	@g++ -c $< -o $@ -std=c++11

# Exécutables de test des classes :

io_main.exe: objects/io_main.o objects/io.o
	@echo "Compiling $@ ..."
	@g++ $^ $(OCARTE) $(OCOMPETENCE) -o $@ -std=c++11
fonctionsjeu.exe: objects/fonctionsjeu.o objects/fonctionsjeu_main.o archives/io.a
	@echo "Compiling $@ ..."
	@g++ $^ $(OIO) $(OENTITE) $(OCARTE) $(OMONSTRE) $(OCOMPETENCE) -o $@ -std=c++11
