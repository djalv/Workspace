import pandas as pd
import sqlite3

conn = sqlite3.connect('base.db3')

#### IMPORT CSV MOTORISTAS HABILITADOS
def importMotoristas(conn):
    url = "./motoristas_habilitados_11_2021.csv"
    df = pd.read_csv(url, encoding="ISO-8859-1", sep=';')
    motoristas = df[['razao_social', 'cnpj', 'nome_motorista', 'cpf', 'vigencia_do_cadastro']]
    motoristas = motoristas.drop_duplicates() # Mod1
    motoristas = motoristas.rename(columns={'razao_social': 'RAZAO_SOCIAL', 'cnpj': 'CNPJ', 'nome_motorista': 'NOME', 'cpf': 'CPF', 'vigencia_do_cadastro': 'DTVIGENCIA'}) #Mod1
    motoristas['DTVIGENCIA'] = motoristas['DTVIGENCIA'].apply(pd.to_datetime, format='%d/%m/%Y')
    motoristas.to_sql('MOTORISTAS', conn, if_exists='append', index = False)
#####################################
#### IMPORT CSV LICENCAS
def importLicensa(conn):
    url = "./licenca_viagem_nacional_2021_11.csv"
    df = pd.read_csv(url, encoding="ISO-8859-1", sep=';')
    licencas = df[['data_inicio_viagem', 'data_fim_viagem', 'cnpj', 'razao_social', 'placa', 'numero_licenca_viagem', 'municipio_origem', 'uf_municipio_origem', 'municipiodestino', 'uf_municipio_destino', 'total_passageiros']]
    licencas = licencas.drop_duplicates()
    #data_inicio_viagem;data_fim_viagem;cnpj;razao_social;placa;numero_licenca_viagem;municipio_origem;uf_municipio_origem;municipiodestino;uf_municipio_destino;total_passageiros
    licencas = licencas.rename(columns={'data_inicio_viagem': 'DTINICIALVIAGEM', 'data_fim_viagem': 'DTFINALVIAGEM', 'cnpj': 'CNPJ', 'razao_social': 'RAZAO_SOCIAL', 'placa': 'PLACA', 'numero_licenca_viagem': 'NRLICENSA', 'municipio_origem': 'MUNICIPIO_ORIGEM', 'uf_municipio_origem': 'UF_MUNICIPIO_ORIGEM', 'municipiodestino': 'MUNICIPIO_DESTINO', 'uf_municipio_destino': 'UF_MUNICIPIO_DESTINO', 'total_passageiros': 'TOTAL_PASSAGEIROS'})
    licencas[['DTINICIALVIAGEM', 'DTFINALVIAGEM']] = licencas[['DTINICIALVIAGEM', 'DTFINALVIAGEM']].apply(pd.to_datetime, format='%d/%m/%Y')
    licencas.to_sql('LICENCAS', conn, if_exists='append', index = False)
#####################################
def deleteTable(conn, tableName):
    cur = conn.cursor()

    cur.execute("DELETE FROM " + tableName)

    conn.commit()
def createTableEmpresa(conn):
    cur = conn.cursor()
    cur.execute("CREATE TABLE EMPRESA (CNPJ TEXT, RAZAO_SOCIAL TEXT )")

def createTableLocal(conn):
    cur = conn.cursor()
    cur.execute("CREATE TABLE LOCAL (ID INTEGER PRIMARY KEY AUTOINCREMENT, UF TEXT, MUNICIPIO TEXT)")
    conn.commit()

def preencheLocal(conn):
    cur = conn.cursor()
    cur.execute("INSERT INTO LOCAL (UF, MUNICIPIO) SELECT UF, MUNICIPIO FROM ( SELECT UF_MUNICIPIO_ORIGEM AS UF, MUNICIPIO_ORIGEM AS MUNICIPIO FROM LICENCAS UNION ALL SELECT UF_MUNICIPIO_DESTINO AS UF, MUNICIPIO_DESTINO AS MUNICIPIO FROM LICENCAS ) GROUP BY UF, MUNICIPIO ORDER BY UF, MUNICIPIO")
    conn.commit()
def dropTable(conn, tableName):
    try:
        cur = conn.cursor()
        cur.execute("DROP TABLE " + tableName)
        conn.commit()
    except:
        print("Table " + tableName + " not exists")

dropTable(conn, "LICENCAS")
dropTable(conn, "MOTORISTAS")
dropTable(conn, "LOCAL")

importMotoristas(conn)
importLicensa(conn)

createTableLocal(conn)
preencheLocal(conn)
conn.close()