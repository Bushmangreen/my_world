import pandas as pd
import sqlite3
import csv
class DS_Babel():

    def connect_to_database(self, sql_file):
        try:
            connection = sqlite3.connect(sql_file)
            print("Opened database successfully")
        except Exception as e:
            print("Error during connection:", str(e))
        return connection

    def get_table_name(self, connection):
        cursor = connection.cursor()
        cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
        table_name = cursor.fetchall()
        return table_name[0][0]

    def csv_to_sql(self, csv_file, connection):
        data = pd.read_csv(csv_file)
        df = pd.DataFrame(data)
        #print(df.columns)

        #create SQL table
        cur = connection.cursor()
        cur.execute('DROP TABLE IF EXISTS volcanos')
        cur.execute('''
        CREATE TABLE volcanos(
            "volcano_name" TEXT,
            "country" TEXT,
            "type_v" TEXT,
            "latitude" TEXT,
            "longitude" TEXT,
            "elevation" TEXT
        )
        ''')

        # Insert DataFrame to Table
        for index, row in df.iterrows():
            volcano_name = row[0]
            country = row[1]
            type_v = row[2]
            latitude = row[3]
            longitude = row[4]
            elevation = row[5]
            cur.execute('''INSERT INTO volcanos(volcano_name, country, type_v,
                        latitude, longitude, elevation) VALUES (?, ?, ?, ?, ?, ?)''', 
                        (volcano_name, country, type_v, latitude, longitude, elevation))
            connection.commit()
        connection.close()

    def sql_to_csv(self, connection, table_name):
        my_query = "SELECT * FROM " + table_name
        df = pd.read_sql_query(my_query, connection)
        df.to_csv('all_fault_line.csv', index = False)
        connection.close()

#*********PART I**********  
start = DS_Babel()
connection = start.connect_to_database('list_volcano.db')
start.csv_to_sql('list_volcano.csv', connection)

#*********PART II**********        
start = DS_Babel()
connection = start.connect_to_database('all_fault_line.db')
table_name = start.get_table_name(connection)
start.sql_to_csv(connection, table_name)

