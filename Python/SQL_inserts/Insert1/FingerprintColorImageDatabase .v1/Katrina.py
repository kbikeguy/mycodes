# Import the os module, for the os.walk function
import os


def main():
    # open the file filled with known file names in read mode
    fileObj = open('filesList.txt', 'r')
    # fill a list with the file names then close the file
    prevKnownFiles = fileObj.read().split()
    fileObj.close()
    # learn the last know count of files
    oldFileCount = prevKnownFiles.__len__()

    # traverse the tree of directories and files
    rootDirectory = 'WRITE YOUR ROOT DIRECTORY PATH HERE'  # TODO ADD YOUR OWN ROOT DIRECTORY FILEPATH
    currFiles = []
    for dirName, subdirList, fileList in os.walk(rootDirectory):
        for file in fileList:
            # build a list of all the current files
            if 'CHNL' in file:
                currFiles.append(file)

    # check if there are new files
    newFileCount = currFiles.__len__()
    if oldFileCount != newFileCount:
        # create a file with the names of the new files in write mode
        newFilesObj = open('newFiles.txt', 'w')
        # open the file with previous known file names and append on the new files in append mode
        fileObj = open('filesList.txt', 'a')

        # loop through the new file list
        for file in currFiles:
            # check if a file in the new list is not in the old list
            if file not in prevKnownFiles:
                # write the filename to the new file text file
                newFilesObj.write('%s\n' % file)
                # append new filename to the original file text file
                fileObj.write('%s\n' % file)

        # close files
        newFilesObj.close()
        fileObj.close()


if __name__ == '__main__':
    main()
