"""
Authors: Riley Campbell, Lane Moseley
Class: CSC-372 Analysis of Algorithms, Fall 2020
Description: Strongly Connected Components for Social Networks
"""
from socialnetwork import SocialNetwork
from collections import deque
import random
import matplotlib.pyplot as plt
import networkx as nx


def getPeople():
    """
    this method requests a name of a file and then reads the names of that file into a list.
    the first and last names needs to separated by a space and one person's name ner line in the file
    :return: names - the list of names
    """
    filename = input("Enter file name: ")
    names = list()
    try:
        # trying to open a file in read mode
        file = open(filename, 'r')

        for name in file:
            names.append(name.strip())

        file.close()
    except FileNotFoundError:
        print("File does not exist")

    return names


def printResults():
    pass


def friendGenUtil(name, friends, nameList):

    nameList.remove(name)

    for key, val in friends.items():
        if name in val:
            nameList.remove(key)

    return nameList


def randomFriendGenerator(names):
    """
    this method takes in a list of names and constructs a dictionary out of those names.
    each person will know (names.size() - 1) // 3 people if the list is greater than 2. if the list size is 2, than
    each person will know each other. if the list is less than 2, it will return an a dictionary of that person as the
    key but with no values. first the list is iterated through and a name is pulled out one at a time. then a new list
    will be made out of everyone except the current person. then a friend list will be randomly generated out of those
    people of the predetermined size. lastly, these will be added to the dictionary with the person as the key and the
    list of friends as the value.

    :param names: the list of names to build friendships from
    :return: the dictionary of friendships
    """
    friends = dict()

    # special case
    if len(names) == 1:
        friends[names[0]] = []
        return friends

    if len(names) == 2:
        friends[names[0]] = [names[1]]
        friends[names[1]] = []
        return friends

    # set the friend list size
    if len(names) == 3:
        sampleSize = 1
    elif len(names) < 7:
        sampleSize = (len(names) - 1) // 2
    else:
        sampleSize = (len(names) - 1) // 3

    for name in names:
        newNames = friendGenUtil(name, friends, names.copy())
        # each person knows one and up to sampleSize of the list
        if len(newNames) != 0:
            friends[name] = random.sample(newNames, k=random.randrange(1, min(len(newNames) + 1, sampleSize + 1)))
        else:
            friends[name] = []

    return friends


def stronglyConnectedComp():
    # python stack class
    stack = deque()


def buildEdges(friends, G):
    for key, values in friends.items():
        for value in values:
            G.add_edge(key, value)


def main():
    names = getPeople()

    G = nx.DiGraph()
    G.add_nodes_from(names)
    friendsDict = randomFriendGenerator(names)
    buildEdges(friendsDict, G)

    plt.figure()

    nx.draw_networkx(G, with_labels=True, node_color='green')
    plt.show()

    network = SocialNetwork(friendsDict)
    network.connected_components()


if __name__ == "__main__":
    main()
