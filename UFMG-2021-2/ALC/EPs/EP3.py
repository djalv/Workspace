import numpy as np

nome = "Alvaro Candido de Oliveira Neto"
matricula = 2019117198

def EP_answers(A, B):
    import numpy as np
    ################### NÃO ALTERE DENTRO DA SEÇÃO ABAIXO ###################
    np.random.seed(1)
    U, Sigma, Sigma_vet, Vt, imgReconst_3, log_Sigma, cumul_Sigma, rmseReconst_3 = [None]*8
    imgReconst_10, rmseReconst_10, imgReconst_100 = [None]*3
    rmseReconst_100, imgReconst_500, rmseReconst_500 = [None]*3
    uso_k_10, uso_k_100, uso_k_500, lim_energ = [None]*4
    B_media, Bm, S, w2, V2, valores_sing, Sigma_vals_sing, Sigma_inv, U2_10, imgs2_10 = [None]*10
    #########################################################################

    ### PARTE 1

    ## 1.1
    U, Sigma_vet, Vt = np.linalg.svd(A)
    
    ## 1.2
    Sigma = np.diag(Sigma_vet)
    
    ## 1.3
    def reconstrucao_aproximada(u, sigma, vt, k):
        return np.matrix(u[:,:k]) * sigma[:k,:k,] * np.matrix(vt[:k,:])

    imgReconst_3 = reconstrucao_aproximada(U, Sigma, Vt, 3)
    
    ## 1.4
    log_Sigma = np.log(Sigma_vet)
    cumul_Sigma = np.cumsum(Sigma_vet)
    
    ## 1.5
    def calcula_RMSE(img, imgReconst):
        return np.linalg.norm(img - imgReconst)

    rmseReconst_3 = calcula_RMSE(A, imgReconst_3)
    
    ## 1.6
    imgReconst_10 = reconstrucao_aproximada(U, Sigma, Vt, 10)
    imgReconst_100 = reconstrucao_aproximada(U, Sigma, Vt, 100)
    imgReconst_500 = reconstrucao_aproximada(U, Sigma, Vt, 500)

    rmseReconst_10 = calcula_RMSE(A, imgReconst_10)
    rmseReconst_100 = calcula_RMSE(A, imgReconst_100)
    rmseReconst_500 = calcula_RMSE(A, imgReconst_500)
    
    ## 1.7
    def calcula_qtd_elementos(U, Sigma_vet, Vt):
        return U.size + Sigma_vet.size + Vt.size

    uso_k_10 = calcula_qtd_elementos(U[:,:10], Sigma_vet[:10], Vt[:10,:])
    uso_k_100 = calcula_qtd_elementos(U[:,:100], Sigma_vet[:100], Vt[:100,:])
    uso_k_500 = calcula_qtd_elementos(U[:,:500], Sigma_vet[:500], Vt[:500,:])
   
    ## 1.8
    def get_limite(min_nrg, cumul_Sigma, k):
        for k in range(0, cumul_Sigma.size):
            if(cumul_Sigma[k]/cumul_Sigma[-1] >= min_nrg):
                return k

    lim_energ = get_limite(0.8, cumul_Sigma, 10)
    

    ### PARTE 2
    ## Insira seu código aqui

    ## 2.1
    B_media = np.mean(B, axis=0)
    Bm = B - B_media
    

    ## 2.2
    BmT = np.transpose(Bm)
    S = np.matrix(BmT) * np.matrix(Bm)
    
    ## 2.3
    w2, V2 = np.linalg.eig(S)
    ind = np.argsort(-1*w2, axis=0)

    w2 = w2[ind]
    V2 = V2[:, ind]

    ## 2.4
    valores_sing = np.sqrt(w2)
    

    ## 2.5
    Sigma_vals_sing = np.diag(valores_sing)
    Sigma_inv = np.linalg.inv(Sigma_vals_sing)
    

    ## 2.6
    U2_10 = Bm * V2 * Sigma_inv
    imgs2_10  = reconstrucao_aproximada(U2_10, Sigma_vals_sing, V2, 200)
    

    ################### NÃO ALTERE DENTRO DA SEÇÃO ABAIXO ###################
    answers = {
        "1.1.1" : U,
        "1.1.2" : Sigma_vet,
        "1.1.3" : Vt,
        "1.2" : Sigma,
        "1.3" : imgReconst_3,
        "1.4.1" : log_Sigma,
        "1.4.2" : cumul_Sigma,
        "1.5" : rmseReconst_3,
        "1.6.1" : imgReconst_10,
        "1.6.2" : rmseReconst_10,
        "1.6.3" : imgReconst_100,
        "1.6.4" : rmseReconst_100,
        "1.6.5" : imgReconst_500,
        "1.6.6" : rmseReconst_500,
        "1.7.1" : uso_k_10,
        "1.7.2" : uso_k_100,
        "1.7.3" : uso_k_500,
        "1.8" : lim_energ,
        "2.1.1" : B_media,
        "2.1.2" : Bm,
        "2.2" : S,
        "2.3.1" : w2,
        "2.3.2" : V2,
        "2.4" : valores_sing,
        "2.5.1" : Sigma_vals_sing,
        "2.5.2" : Sigma_inv,
        "2.6.1" :  U2_10,
        "2.6.2" : imgs2_10
    }
    return answers
    ##########################################################################

