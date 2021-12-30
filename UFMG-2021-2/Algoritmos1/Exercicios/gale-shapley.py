import numpy as np

def gale_shapley(hospitals, students, n):
    withoutpairs = list(range(n)) # Hospitais sem pares
    stPair = [None] * n # Pares dos estudantes
    hsPair = [None] * n # Pares dos Hospitais

    nextHsChoice = [0] * n # Array para armazenar a prx escolha do hospital

    while withoutpairs:
        hs = withoutpairs[0] # Escolhe o primeiro hospital hs sem par
        hsPreferences = hospitals[hs] # Carrega a lista de preferencia do hospital hs

        st = hsPreferences[nextHsChoice[hs]] # Armazena o proximo estudante st da lista de hs
        stPreferences = students[st] # carrega a lista de preferencia do estudante st

        currentHs = stPair[st] # Armazena o atual par do estudante st

        if currentHs == None:
            # Caso em que não há
            # hospital emparelhado com o estudante

            # Atribui os pares
            stPair[st] = hs
            hsPair[hs] = st

            # A proxima escolha do hospital
            # é o proximo estudante da sua lista de preferencia 
            nextHsChoice[hs] = nextHsChoice[hs] + 1
            
            # Remove o hospital da lista de sem pares
            withoutpairs.pop(0)
        else:
            # Caso em que o estudante possui um par


            currentIndex = np.where(stPreferences == currentHs)
            hsIndex = np.where(stPreferences == hs)

            if currentIndex > hsIndex:
                stPair[st] = hs
                hsPair[hs] = st

                nextHsChoice[hs] = nextHsChoice[hs] + 1

                withoutpairs.pop(0)
                withoutpairs.insert(0,currentHs)
            else:
                nextHsChoice[hs] = nextHsChoice[hs] + 1
    
    return hsPair

s = np.array([[1,0,2], [0,1,2], [1,0,2]])
h = np.array([[0,1,2], [1,0,2], [0,1,2]])

pairs = gale_shapley(h,s,len(s))

print("(0, {}), (1, {}), (2, {})".format(pairs[0], pairs[1], pairs[2]))