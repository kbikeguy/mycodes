# Import the os module, for the os.walk function
import os


def fillSubjects(ID, file):
    file.write('# __________INSERTS FOR SUBJECT %s____________\n' % ID)
    file.write("INSERT INTO Subjects\n(subjectID)\nVALUES('%s');\n\n" % ID)


def fillFingers(file, hand, index, fID, subID):
    file.write("INSERT INTO Fingers\n")
    file.write("(handID, fingerIndex, fingerID, subjectID)\n")
    file.write("VALUE(%s, %s, '%s', '%s');\n\n" % (hand, index, fID, subID))


def fillImages(file, address, imgID, fID, width, height, res):
    file.write("INSERT INTO Images\n")
    file.write("(image, imageID, fingerID, width, height, resolution)\n")
    file.write("VALUE('%s', '%s', '%s', %s, %s, %s);\n\n" % (address, imgID, fID, width, height, res))


def fillFeatures(file, imageID, featureID, num):
    file.write("INSERT INTO Features\n")
    file.write("(imageID, featureID, minutiaesCount)\n")
    file.write("VALUE('%s', '%s', %d);\n\n" % (imageID, featureID, num))


def getMinutiaes(attributes):
    minutiaeList = attributes.readlines()

    # separate values
    i = 0
    for line in minutiaeList:
        temp = line.split(' ')
        minutiaeList[i] = list(temp[:3])
        i = i + 1

    return minutiaeList


def fillMinutiaes(file, minutiaes, featureID):
    count = 1

    for minutiae in minutiaes:
        minutiaeID = featureID + '.' + str(count)
        count += 1
        coordX = int(minutiae[0])
        coordY = int(minutiae[1])
        theta = float(minutiae[2])
        file.write('INSERT INTO Minutiaes\n')
        file.write('(minutiaeID, featureID, coordX, coordY, theta)')
        file.write("VALUE('%s', '%s', %d, %d, %d);\n\n" % (minutiaeID, featureID, coordX, coordY, theta))


def main():
    # Set the directory you want to start from
    rootDir = 'C:\\Users\\7356506\\Desktop\\SDSMT\\Fall2020\\Senior Design\\Nanoparticle Images Separated by Subject'
    f = open("C:\\Users\\7356506\\Documents\\imageINSERTs.sql", 'w')

    # SET UP VARIABLES
    featureCount = 1
    subjectID = ''
    handID = 'NULL'
    imageID = ''
    width = '500'
    height = '500'
    resolution = 'NULL'
    for dirName, subdirList, fileList in os.walk(rootDir):
        # skip the first iteration
        if dirName == rootDir:
            continue

        # get the subject id and fill subject table
        if dirName[-1].isalpha():
            subjectID = dirName[-1]
            fillSubjects(subjectID, f)

        # get the finger id and fill finger table
        if dirName[-1].isnumeric():
            fingerIndex = dirName[-1]
            fingerID = subjectID + '.' + fingerIndex
            fillFingers(f, handID, fingerIndex, fingerID, subjectID)
            for file in fileList:
                # if file is an image
                if '.png' in file:
                    image = dirName + '\\' + file  # TODO UPDATE FOR SERVER ADDRESS
                    imageID = fingerID + '.' + file[:-4]
                    fillImages(f, image, imageID, fingerID, width, height, resolution)
                # file is attributes
                else:
                    # fill features table
                    featureObj = open(dirName + '\\' + file, 'r')
                    featureID = imageID + '.' + str(featureCount)
                    featureCount = featureCount + 1
                    minutiaes = getMinutiaes(featureObj)
                    featureObj.close()
                    fillFeatures(f, imageID, featureID, len(minutiaes))

                    # fill minutiaes table
                    fillMinutiaes(f, minutiaes, featureID)

    f.close()


if __name__ == '__main__':
    main()
