import csv
import re

# getting each row from the csv and each row is splitted acording to "|"
def get_data():
    with open('Warriors_vs_Thunders.csv') as stats_csv:
        csv_reader = csv.reader(stats_csv, delimiter='|')
        play_by_play = []
        for row in csv_reader:
            play_by_play.append(row)
    return play_by_play


# function is used to find all unique players from csv_file
def get_all_player_names(play_by_play): 
    pattern = re.compile(r'(\w\. [a-z]+)',re.I) # regular expression to match pattern "K. Name" format, re.I for ignoring letter case sensitivty
    player_names = []
    for event in play_by_play:
        name = pattern.search(event[-1])
        if name:
            player_names.append(name.group(0))
            if name.group(1):
                player_names.append(name.group(1))
    player_names = list(set(player_names)) # get the unique list of players

    return player_names                           

#function used to match player to his relevant team, 
#output the team name and if it is away or home
def match_to_team(event):
    RELEVANT_TEAM = 2
    AWAY_TEAM = 3
    HOME_TEAM = 4
    if event[RELEVANT_TEAM] == event[HOME_TEAM]:
        return ['home_team',event[HOME_TEAM]]
    else:
        return ['away_team',event[AWAY_TEAM]] 

#this function is used to process play_by_play data, which basically words or comments
#so in order to process the words and find the patterns to find stats
#regular expression were used
def process_play_by_play(play_by_play, player_names):
    
    #list of regular expressions to match all the stats and get the stats of the player
    
    fg_pattern = re.compile(r'(\w\. [a-z]+)? makes (2-pt|3-pt)', re.I) # this is, to match Field Goal scored, any 2-pt or 3-pt 
    fga_pattern = re.compile(r'(\w\. [a-z]+)? \w+ (2-pt|3-pt)', re.I)# this is, to match attempts
    p3_pattern = re.compile(r'(\w\. [a-z]+)? makes 3-pt', re.I)# this is, to match 3 pt scores only
    p3a_pattern = re.compile(r'(\w\. [a-z]+)? \w+ 3-pt', re.I) # this is, to match attempts 3 pt scores 
    ft_pattern = re.compile(r'(\w\. [a-z]+)? makes ([a-z ]+)? ?free throw', re.I)# this is, to match free throws scored 
    fta_pattern = re.compile(r'(\w\. [a-z]+)? \w+ ([a-z ]+)? ?free throw (\d) of (\d)', re.I)# this is, to match free throws attempts but not scored 
    orb_pattern = re.compile(r'Offensive rebound \w+ (\w\. [a-z]+)', re.I)# this is, to match offensive rebounds
    drb_pattern = re.compile(r'Defensive rebound \w+ (\w\. [a-z]+)', re.I)# this is, to match defensive rebounds
    ast_pattern = re.compile(r'assist by (\w\. [a-z]+)', re.I)# this is, to match assists 
    stl_pattern = re.compile(r'steal by (\w\. [a-z]+)', re.I)# this is, to match steals 
    blk_pattern = re.compile(r'block by (\w\. [a-z]+)', re.I)# this is, to match blocks 
    tov_pattern = re.compile(r'turnover by (\w\. [a-z]+)', re.I) # this is, to match turnovers
    pf_pattern = re.compile(r'foul by (\w\. [a-z]+)', re.I)# this is, to match fouls
    
    list = []  
    
    for player in player_names: # we take each NBA player 
        
        teams = {'home_team': {'name': '', 'players_data': {}}, 'away_team': {'name': '', 'players_data': {}}}    
        data = {"player_name": '', "FG": 0, "FGA": 0, "FG%": 0, "3P": 0, "3PA": 0, "3P%": 0, "FT": 0, "FTA": 0, "FT%": 0, "ORB": 0, "DRB": 0, "TRB": 0, "AST": 0, "STL": 0, "BLK": 0, "TOV": 0, "PF": 0, "PTS": 0}
        data['player_name'] = player
        player_info = []
        for event in play_by_play: # and loop through the play_by_play stats and look for matches be it foul 2-pt score or whatever matches
        
            fg = fg_pattern.search(event[-1]) 
            if fg:
                if fg.group(1) == player:
                    data['FG'] += 1
           
            fga = fga_pattern.search(event[-1])        
            if fga:
                if fga.group(1) == player:
                    data['FGA'] += 1
                    player_info = match_to_team(event)
            p3 = p3_pattern.search(event[-1]) 
            if p3:
                if p3.group(1) == player:
                    data['3P'] += 1 
        
            p3a = p3a_pattern.search(event[-1]) 
            if p3a:
                if p3a.group(1) == player:
                    data['3PA'] += 1      
                    player_info = match_to_team(event)
            ft = ft_pattern.search(event[-1])
            if ft:
                if ft.group(1) == player:
                    data['FT'] += 1  
        
            fta = fta_pattern.search(event[-1])
            if fta:
                if fta.group(1) == player:
                    data['FTA'] += 1  
                    player_info = match_to_team(event)
            orb = orb_pattern.search(event[-1]) 
            if orb:
                if orb.group(1) == player:
                    data['ORB'] += 1 
                    player_info = match_to_team(event)
            drb = drb_pattern.search(event[-1]) 
            if drb:
                if drb.group(1) == player:
                    data['DRB'] += 1 
                    player_info = match_to_team(event)
            ast = ast_pattern.search(event[-1])
            if ast:
                if ast.group(1) == player:
                    data['AST'] += 1
                    player_info = match_to_team(event)
            stl = stl_pattern.search(event[-1])
            if stl:
                if stl.group(1) == player:
                    data['STL'] += 1
                    player_info = match_to_team(event)
            blk = blk_pattern.search(event[-1])
            if blk:
                if blk.group(1) == player:
                    data['BLK'] += 1                    
                    player_info = match_to_team(event)
            tov = tov_pattern.search(event[-1])
            if tov:
                if tov.group(1) == player:
                    data['TOV'] += 1
                    player_info = match_to_team(event)
            pf = pf_pattern.search(event[-1])
            if pf:
                if pf.group(1) == player:
                    data['PF'] += 1;   
                    player_info = match_to_team(event)
        if data['FGA']:# sometimes FGA is zero so we have avoid deviding number by zero
            data['FG%'] = data['FG']/data['FGA'] # FG% calculation which is basically FG/FGA same for the rest
        if data['3PA']:
            data['3P%'] = data['3P']/data['3PA']
        if data['FTA']:     
            data['FT%'] = data['FT']/data['FTA']
        data['TRB'] =  data['ORB'] + data['DRB']
        data['PTS'] = (data['FG'] - data['3P']) * 2 + data['3P'] * 3 + data['FT']
        
        for k, v in data.items(): 
            if type(data[k]) == float:
                data[k] = round(v, 3) # rounding dictionary values, since some of them are rediculously long

        teams[player_info[0]]['name'] = player_info [1]
        teams[player_info[0]]['players_data'] = data 
        list.append(data) # if we append teams into list (list.append(teams)),  it will bulky list of dictionaries that will contain all the parsed play_by_play info
    return list           # as for the task we just return data, whihc is list of each player stats 

#Part II

def print_header(dict): 
    print(*dict.keys(), sep = '\t') 

def print_players(data):
    for dictionary in data:
        result = [dictionary[x] for x in dictionary.keys()]
        print(*result, sep = '\t')

def total_calc(data):
    result = ['Team Totals']
    dictionary = data[0]
    keys = list(dictionary.keys())
    col = 1
    while col < len(keys):
        sum = 0
        index = 0
        while index < len(data):
            dictionary = data[index]
            sum += dictionary[keys[col]]
            index += 1
        sum = round(sum, 3)
        result.append(sum)
        col += 1
    return result

def print_total(data):
    print(*total_calc(data), sep= '\t')


def print_total(data):
    result = total_calc(data)
    print(*result, sep = '\t')

def print_nba_game_stats(team_dict):
    print_header(team_dict[0])
    print_players(team_dict)
    print_total(team_dict)

play_by_play = get_data()
player_names = get_all_player_names(play_by_play)
data = process_play_by_play(play_by_play, player_names)
print_nba_game_stats(data)


