from bs4 import BeautifulSoup
from bs4 import SoupStrainer
import time
import requests

start_time = time.time()

print("Enter address")
url = input()

source = requests.get(url).text
soup = BeautifulSoup(source, 'lxml')


for findDiv in soup.find_all("div", class_="y-css-1ousnla"):
    if (findDiv.text.find("of") > 0):
        reviewPages = findDiv.text


reviewPages = reviewPages.split('1 of ')
reviewPages = int(reviewPages[1])
print("Amount of pages: " + str(reviewPages))

reviewsList = []
reviewScores = []

for pages in range(reviewPages):
    newUrl = url

    if (pages != 0):
        newUrl = newUrl + "?start=" + str(pages * 10)

    printStatus = "scraping page " + str(pages + 1)
    print(printStatus)

    source = requests.get(newUrl).text
    parseOnlyTags = SoupStrainer(['p', 'div'])
    soup = BeautifulSoup(source, 'lxml', parse_only=parseOnlyTags)


    for score in soup.find_all('div', class_="y-css-1jwbncq"):
        scoreSplit = score["aria-label"].split(" ")
        reviewScores.append(scoreSplit[0])

    for reviews in soup.find_all('p', class_='comment__09f24__D0cxf'):
        reviewsList.append(reviews.text)

with open('tester.txt', 'w', encoding="utf-8") as file:
    for i in range (len(reviewsList)):
        file.write(reviewScores[i])
        file.write(" ")
        file.write(reviewsList[i])
        file.write("\n")
        
print("Scraping complete")
print("--- %s seconds ---" % (time.time() - start_time))