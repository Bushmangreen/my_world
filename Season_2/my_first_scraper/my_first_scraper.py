import requests
from bs4 import BeautifulSoup

def request_github_trending(url):
    response = requests.get("https://github.com/trending")
    return response

def extract(response):
    soup = BeautifulSoup(response.text, 'html.parser')
    return soup

def transform(soup):
    articles = soup.find_all('article')
    my_list = []
    my_dict = {'deverloper': '', 'repository_name': '', 'nbr_stars': ''}
    for article in articles:
        name = article.find('span').get_text().strip('\n /')
        repo = article.find('span').next_sibling.strip('\n ')
        number_of_stars = article.find(attrs={'aria-label':'star'}).next_sibling.strip('\n ')
        
        my_dict['deverloper'] = name
        my_dict['repository_name'] = repo
        my_dict['nbr_stars'] = number_of_stars
        
        copy_dict = my_dict.copy()
        my_list.append(copy_dict)
    return my_list

def format(my_list):
    column_names = ",".join(my_list[0].keys())
    column_names += '\n'
    
    csv_string = ""
    
    csv_string += column_names

    
    for each in my_list:
        line = ",".join(each.values())
        line += '\n'
        csv_string += line

    return csv_string
    

url ="https://github.com/trending"
response = request_github_trending(url)
soup = extract(response)
my_list = transform(soup)
print(format(my_list))