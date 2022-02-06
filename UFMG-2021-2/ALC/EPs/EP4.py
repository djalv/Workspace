'''
Ambiente de Programação Virtual (VPL)

----- >Instruções para baixar o EP: <---------
1 - Baixe o arquivo zip do EP4 na página principal do curso.
2 - Extraia o conteúdo, que deverá conter o arquivo notebook (.ipynb).
3 - Rode o .ipynb no Google Colab (é necessário ter uma conta do google, mas é bem prático), ou no Jupyter Notebook.
4 - Programe sua solução 


----- >Instruções para avaliar sua solução: <---------
1 - Após implementar sua solução, converta seu .ipynb para .py no menu do Jupyter ou Google Colab. Isso irá gerar um arquivo .py comum (Python Script).
2 - Cole o conteúdo do arquivo .py gerado na aba 'Editar' no VPL do EP. Também é possível submeter como um arquivo em sua máquina na aba 'Enviar', selecionando o arquivo e depois clicando em 'avaliar'.
3 - Clique no botão 'Salvar' e depois 'Avaliar' 
4 - Verifique o output e sua nota, que irão aparecer do lado direito da interface do VPL. É possível aumentar a janela de texto caso necessário.
5 - Caso tenha alguma coisa errada, o corretor irá indicar o erro.
6 - Corrija os erros em seu script, e repita a partir do passo 1 caso queria reenviar sua solução.

'''
import numpy as np
import matplotlib.pyplot as plt

X = np.array([[7, 12, 8]])
Y = np.array([[5, 10, 15]])

plt.plot(X, Y, )

mu_x = np.mean(X)
mu_y = np.mean(Y)

