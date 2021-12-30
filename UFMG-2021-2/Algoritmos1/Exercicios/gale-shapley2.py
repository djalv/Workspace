import numpy as np

def gale_shapley2(hsPreferences, stPreferences, n, m):
    # Hospitais sem pares
    unpairsHospitals = list(range(n))

    # Pares de cada hospipal
    studentPairs = [None] * m
    # Pares de cada estudante
    hospitalPairs = [None] * n

    # Proxima escolha de cada hospital
    nextHsChoice = [0] * n

    # Enquanto há hospitais sem par, continua
    while unpairsHospitals:
        # Obtem o primeiro hospital h da lista sem par
        hospital = unpairsHospitals[0]

        # Carrega a lista preferencial de h
        listHsPreferences = hsPreferences[hospital]

        # Obtem o estudante s que o hospital h irá escolher
        student = listHsPreferences[nextHsChoice[hospital]]
        
        # Carrega a lista de preferencia de s
        listStPreferences = stPreferences[student]
        
        # Obtem o par atual do estudante s
        currentPair = studentPairs[student]

        if currentPair == None:
            # Caso em que o estudante s
            # não tem par

            # Atribui os pares
            studentPairs[student] = hospital
            hospitalPairs[hospital] = student

            # Atualiza a prox escolha do hospital h
            # para o proximo estudante 
            nextHsChoice[hospital] = nextHsChoice[hospital] + 1
            
            # Retira o primeiro hospital da lista
            # de hospitais sem pares 
            unpairsHospitals.pop(0)
        else:
            # Caso em que s possui um par

            # Obtemos o rank do atual par do estudante s
            # em sua lista de preferencia 
            currentPairRank = np.where(listStPreferences == currentPair)
            
            # Obtemos o rank do hospital h
            # na lista de preferencia de s 
            HsRank = np.where(listStPreferences == hospital)

            if currentPairRank > HsRank:
                # Caso em que o hospital s
                # está melhor colocado que o atual par de s

                studentPairs[student] = hospital
                hospitalPairs[hospital] = student
                nextHsChoice[hospital] = nextHsChoice[hospital] + 1
                unpairsHospitals.pop(0)

                # add o atual par para a lisa de hospitais sem pares
                unpairsHospitals(0, currentPairRank)
            else:
                # Atualiza a prox escolha do hospital h
                # para o proximo estudante 
                nextHsChoice[hospital] = nextHsChoice[hospital] + 1
    
    return hospitalPairs

h = np.array([[3,1,2], [2,0,1], [0,1,3]])
s = np.array([[0,1,2], [2,1,0], [2,1,0], [0,1,2]])

print(gale_shapley2(h,s,3,4))