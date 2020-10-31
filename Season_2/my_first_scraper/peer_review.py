url="https://github.com/trending"
BASE_URL = 'https://github.com'

def request_github_trending(url):
    import requests
    page = requests.get(url)
    return page

def extract(page):
    import bs4
    sup = bs4.BeautifulSoup(page.content, 'html.parser')
    return sup
    

def transform(html_repos):
    import bs4
    projects = []

    rows = html_repos.find_all(class_='Box-row')

    for row in rows:
        developer = get_developer(row)
        repos_name = get_repos_name(row)
        description = get_description(row)

        stars = get_stars(row)
        language = get_language(row)
        url = get_url(row)

        projects.append({
            'deverloper': developer,
            'repository_name': repos_name,
            'description': description,
            'nbr_stars': stars,
            'language': language,
            'url': url
            })

    return projects

def get_developer(row):
    header = row.find(class_='lh-condensed')
    link = header.find('a')
    text = link.get_text()
    last_word = text.split(' ')[-8]
    
    return last_word.replace('\n', '')

def get_repos_name(row):
    header = row.find(class_='lh-condensed')
    link = header.find('a')
    text = link.get_text()
    last_word = text.split(' ')[-1]
    return last_word.replace('\n', '')


def get_description(row):
    p = row.find('p')

    if p is None:
        return None
    else:
        text = p.getText()
        stripped = text.strip()
        return stripped.replace('\n', '')


def get_stars(row):
    f6 = row.find(class_='f6')
    links = f6.find_all('a')
    star_link = links[0]

    text = star_link.get_text()
    replaced = text.replace('\n', '')
    return replaced.strip()


def get_language(row):
    f6 = row.find(class_='f6')
    spans = f6.find_all('span')
    span = spans[0]
    language_span = span.find('span', itemprop='programmingLanguage')

    if language_span is None:
        return None
    else:
        return language_span.get_text()


def get_url(row):
    header = row.find(class_='lh-condensed')
    link = header.find('a')
    return BASE_URL + link['href']

def format(repositories_data):
    values= ""
    for i in repositories_data:
        values += i['deverloper']+","+i['repository_name']+","+ i['nbr_stars']+"\n"
    return values

page = request_github_trending(url)
html_repos = extract(page)
repositories_data = transform(html_repos)
out = format(repositories_data)
print(out)
    