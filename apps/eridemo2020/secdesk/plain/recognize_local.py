import face_recognition
import cv2
import pickle
import numpy
import numpy as np

############################################## LOCAL ###################################################
def calcEncodings(imageFile, methodName):
    # load the input image and convert it from BGR to RGB
    image = cv2.imread(imageFile)
    rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    # detect the (x, y)-coordinates of the bounding boxes corresponding
    # to each face in the input image, then compute the facial embeddings
    # for each face
    print("[INFO] recognizing faces using " + methodName)
    boxes = face_recognition.face_locations(rgb, model=methodName)
    encodings = face_recognition.face_encodings(rgb, boxes)
    
    # convert from numpy 1-d array of doubles to list of list of doubles
    # listOfEnc = [[double(j) for j in i] for i in encodings]
    listOfEnc = [[j for j in enc] for enc in encodings]
    listBoxes = [[m for m in n] for n in boxes]

    return [listOfEnc, listBoxes, image]

def overlay(boxes, names, imageFile, ofname):
    image = cv2.imread(imageFile)

    # loop over the recognized faces
    for ((top, right, bottom, left), name) in zip(boxes, names):
        # draw the predicted face name on the image
        cv2.rectangle(image, (left, top), (right, bottom), (0, 255, 0), 2)
        y = top - 15 if top - 15 > 15 else top + 15
        cv2.putText(image, name, (left, y), cv2.FONT_HERSHEY_SIMPLEX,
                0.75, (0, 255, 0), 2)
    # save image with face recognition overlay
    try:
        cv2.imwrite(ofname, image)
    except Exception as e: print(e)

############################################## REMOTE ###################################################
def init_recognizer(modelfile="encodings.pickle.id"): 
    print("[INFO] loading encodings...")
    return pickle.loads(open(modelfile, "rb").read())

def recognize_one(encdbl, data): 
    encoding = np.array(encdbl)

    # convert from numpy 1-d array of doubles to list of list of doubles
    # attempt to match each face in the input image to our known encodings
    matches = face_recognition.compare_faces(data["encodings"], encoding)
    name = "Unknown"

    # check to see if we have found a match
    if True in matches:
        # find the indexes of all matched faces then initialize a
        # dictionary to count the total number of times each face
        # was matched
        matchedIdxs = [i for (i, b) in enumerate(matches) if b]
        counts = {}

        # loop over the matched indexes and maintain a count for
        # each recognized face face
        for i in matchedIdxs:
             name = data["names"][i]
             counts[name] = counts.get(name, 0) + 1

        # determine the recognized face with the largest number of
        # votes (note: in the event of an unlikely tie Python will
        # select first entry in the dictionary)
        name = max(counts, key=counts.get)
    return name
