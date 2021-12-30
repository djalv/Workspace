import numpy as np

nome = ""
matricula = None

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
    ## Insira seu código aqui
    
    ## 1.2
    ## Insira seu código aqui
    
    ## 1.3
    ## Insira seu código aqui
    
    ## 1.4
    ## Insira seu código aqui
    
    ## 1.5
    ## Insira seu código aqui
    
    ## 1.6
    ## Insira seu código aqui
    
    ## 1.7
    ## Insira seu código aqui
   
    ## 1.8
    ## Insira seu código aqui
    

    ### PARTE 2
    ## Insira seu código aqui

    ## 2.1
    ## Insira seu código aqui
    

    ## 2.2
    ## Insira seu código aqui
    
    
    ## 2.3
    ## Insira seu código aqui
    

    ## 2.4
    ## Insira seu código aqui
    

    ## 2.5
    ## Insira seu código aqui
    

    ## 2.6
    ## Insira seu código aqui
    

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

