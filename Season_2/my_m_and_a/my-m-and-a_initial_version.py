import pandas as pd

def clean_gender():

def clean_name():

def clean_city():

def clean_email():
    



def my_m_and_a(content_database_1, content_database_2, content_database_3, sql_name):
    #reading 1 csv file
    df1 = pd.read_csv(content_database_1)

    #print(df1.Gender.unique())
    # cleaning gender column
    df1['Gender'] = df1['Gender'].replace(['M'],'Male')
    df1['Gender'] = df1['Gender'].replace(['F'],'Female')
    df1['Gender'] = df1['Gender'].replace(['0'],'Male')
    df1['Gender'] = df1['Gender'].replace(['1'],'Female')
    #print(df1.Gender.unique())
    
    # removing unnecessary characters and capitalizing first letter of firstname and lastname columns
    #print(df1.head())
    df1['FirstName'] = df1['FirstName'].str.replace('\\','')
    df1['LastName'] = df1['LastName'].str.replace('\\','')
    df1['FirstName'] = df1['FirstName'].str.replace('"','')
    df1['LastName'] = df1['LastName'].str.replace('"','')
    df1['FirstName'] = df1['FirstName'].str.capitalize() 
    df1['LastName'] = df1['LastName'].str.capitalize() 

    #email column lowercase
    df1["Email"] = df1["Email"].str.lower()
    
    # printing null columns
    df1["FirstName"].fillna("Nan", inplace = True) 
    df1["UserName"].fillna("Nan", inplace = True) 

    # city column
    df1['City'] = df1['City'].str.replace('_',' ')
    df1['City'] = df1['City'].str.replace('-',' ')
    df1['City'] = df1['City'].str.title() 
    #print(df1.City.unique())

    # country column
    df1['Country'] = 'USA'
    #print(df1)
    df2 = pd.read_csv(content_database_2, sep = ';', header = None, names = ['Age', 'City', 'Gender', 'Name', 'Email'])
    df2[['FirstName','LastName']] = df2.Name.str.split(expand=True)
    df2.drop('Name', inplace=True, axis=1)
    # cleaning gender column
    df2['Gender'] = df2['Gender'].replace(['M'],'Male')
    df2['Gender'] = df2['Gender'].replace(['F'],'Female')
    df2['Gender'] = df2['Gender'].replace(['0'],'Male')
    df2['Gender'] = df2['Gender'].replace(['1'],'Female')
    
    # removing unnecessary characters and capitalizing first letter of firstname and lastname columns
    df2['FirstName'] = df2['FirstName'].str.replace('\\','')
    df2['LastName'] = df2['LastName'].str.replace('\\','')
    df2['FirstName'] = df2['FirstName'].str.replace('"','')
    df2['LastName'] = df2['LastName'].str.replace('"','')
    df2['FirstName'] = df2['FirstName'].str.capitalize() 
    df2['LastName'] = df2['LastName'].str.capitalize() 
    
    #email column lowercase
    df2["Email"] = df2["Email"].str.lower()

    # city column
    df2['City'] = df2['City'].str.replace('_',' ')
    df2['City'] = df2['City'].str.replace('-',' ')
    df2['City'] = df2['City'].str.title() 

    # country column
    df2['Country'] = 'USA'

    # joining two dataframes
    #df12 = pd.concat([df1, df2], ignore_index=True)
    #print(df12)

    # reading 3rd csv file
    df3 = pd.read_csv("only_wood_customer_us_3.csv", delimiter= '\t', names= ['Gender','Name','Email','Age','City','Country'],
                 header= 0, na_values= ['N/A'])
    df3[['FirstName','LastName']] = df3.Name.str.split(expand=True)
    df3.drop('Name', inplace=True, axis=1)

    # cleaning dataframe from prefixes
    df3 = df3.replace(to_replace=r'string_|integer_|boolean_|character_', value='', regex=True)
    df3['Age'] = df3['Age'].replace(to_replace=r'[a-zA-Z]', value='', regex=True)

    # cleaning gender column
    gender = {'1':'Male', '0':'Female','M': 'Male'}
    df3['Gender'] = df3['Gender'].replace(gender)

    # removing unnecessary characters and capitalizing first letter of firstname and lastname columns
    df3['FirstName'] = df3['FirstName'].str.replace('\\','')
    df3['LastName'] = df3['LastName'].str.replace('\\','')
    df3['FirstName'] = df3['FirstName'].str.replace('"','')
    df3['LastName'] = df3['LastName'].str.replace('"','')
    df3['FirstName'] = df3['FirstName'].str.capitalize() 
    df3['LastName'] = df3['LastName'].str.capitalize() 
   
    # drop the rows without emails
    df3.dropna(inplace=True) 

    #email column lowercase
    df3["Email"] = df3["Email"].str.lower()

    # city column
    df3['City'] = df3['City'].str.replace('_',' ')
    df3['City'] = df3['City'].str.replace('-',' ')
    df3['City'] = df3['City'].str.title() 

    # country column
    df3['Country'] = 'USA'

    df = pd.concat([df1, df2, df3], ignore_index=True)
    print(df.info())

my_m_and_a('only_wood_customer_us_1.csv', 'only_wood_customer_us_2.csv', 'only_wood_customer_us_3.csv', 'plastic_free_boutique.sql')

