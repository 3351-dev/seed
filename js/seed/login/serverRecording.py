from fastapi import FastAPI, Form, File, UploadFile
from pydantic import BaseModel 
from fastapi.middleware.cors import CORSMiddleware
import os, csv, json

app = FastAPI()

origins = ["*"]
origins=[
    "http://127.0.0.1/*",
    "http://localhost",
]
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
#    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

dirname = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__))))
scriptFile = './defaultSetting/shortTest.csv'

def jsonFileConfig(address):
    jsonPath = './audio/'+address
    cmd = 'cp ./defaultSetting/config.json '+jsonPath
    os.system(cmd)

    with open(jsonPath+'/config.json', 'r') as jsonFile:
        jsonData = json.load(jsonFile)
    # print('output_path : '+jsonData['output_path'])
    # print('datasets_path : '+jsonData['datasets'][0]['path'])
    # value = jsonData.get("datasets")[0]['path']
    value = "/usr/share/nginx/demo/audio/"+address+"/filelists"
    # print(value)
    jsonData['output_path']='/usr/share/nginx/demo/audio/'+address+'/'
    jsonData['datasets'][0]['path'] = value

    with open(jsonPath+'/config.json', 'w', encoding='utf-8') as jsonFile:
        json.dump(jsonData, jsonFile, indent='\t')

@app.post('/Recording')
async def recording(fd_audio: UploadFile=File(...)):

    # dirname = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__))))
    audioFilePath = dirname+"/audio/"+fd_audio.filename

    with open(audioFilePath, "wb+") as file_object:
        file_object.write(fd_audio.file.read())

    audioFile = audioFilePath
    getUserID = fd_audio.filename[:-4]
    getUserID = getUserID.split('_')
    print(getUserID[1])

    # 사용자의 ID를가지고 디렉토리별 관리.
    # if not os.path.exists("./audio/"+getUserID[1]):
    #     cmd = "mkdir ./audio/"+getUserID[1]
    #     print('cmd : '+cmd)
    #     os.system(cmd)
    
    audioFileName = "./audio/"+fd_audio.filename[:-4]
    outputPath = "./audio/"+getUserID[1]+"/"+fd_audio.filename[:-4]

    cmd = "ffmpeg -y -i "+audioFileName+".wav -f s16le -acodec pcm_s16le -ar 22050 "+outputPath+".pcm 2>> "+outputPath+".log"
    os.system(cmd) # wav -> pcm, Transform Format
    cmd = "ffmpeg -y -f s16le -ar 22050 -i "+outputPath+".pcm "+outputPath+".wav 2>> "+outputPath+".log" ;
    os.system(cmd) # pcm -> wav
    cmd = "rm ./audio/*.wav"
    os.system(cmd)

    # print(len(os.listdir('./audio/'+getUserID[1])))
    count = round(len(os.listdir('./audio/'+getUserID[1]))/3)
    count = str(count)
    return count

@app.post('/scenario')
async def scenario(scenarioCount: str=Form(...)):
    # dirname = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__))))

    try:
        scenarioCount = (int(scenarioCount))
    except:
        print(scenarioCount)
        # 입력한 이메일 주소로 파일을 생성하거나 있으면 스크립트를 표출
        if not os.path.exists("./audio/"+scenarioCount):
            cmd = "mkdir ./audio/"+scenarioCount
            # print('cmd : '+cmd)
            os.system(cmd)
            # Todo
            # config.json파일을 설정한 path에 맞게 수정하기
            jsonFileConfig(scenarioCount)
        scenarioCount = round(len(os.listdir('./audio/'+scenarioCount))/3)
        scenarioCount = (int(scenarioCount))

    # print(scenarioCount)
    try :
        with open(scriptFile) as f:
            data = f.readlines()[scenarioCount].strip('\n')
        # print(data)

        data = data.split('\t')
        data = data[0]
        print(data)
        return data;
    except:
        return "Next를 눌러 학습을 요청하세요."


@app.post('/merge')
async def merge(id: str=Form(...)):
    path = "./audio/"+id

    if not os.path.exists(path+"/filelists/"):
        cmd = "mkdir "+path+"/filelists/"
        os.system(cmd)
        print('filelist end')
        if not os.path.exists(path+"/filelists/wavs"):
            cmd = "mkdir "+path+"/filelists/wavs"
            os.system(cmd)
            print('wavs end')

    cmd = "cp "+path+"/*.wav "+path+"/filelists/wavs/"
    os.system(cmd)

    count = round(len(os.listdir(path))/3)
    # print(count)

    # 총 스크립트의 갯수 확인
    with open(scriptFile) as f:
        scriptEndPoint = len(f.readlines())
    # print(scriptEndPoint)


    # 시간순으로 정렬
    if not os.path.exists(path+"/timeseries.txt"):
        cmd = "ls -tr "+path+"/*.wav >> "+path+"/timeseries.txt"
        os.system(cmd)

    if not os.path.exists(scriptFile):
        cmd = "cp ."+scriptFile + " " +path
        os.system(cmd)

    ## 정렬 한 파일에서 파일 이름만 가져오기
    # timeSeries = open(path+"/timeseries.txt")
    # for i in timeSeries:
    #     i = i.split('/')
    #     i = i[-1].strip('\n')
    #     # timeSeriesList[i].append(i)
    #     j+=1
    # timeSeries.close()

    timeSeries = open(path+"/timeseries.txt")
    openCSV = open(scriptFile,'r')
    metadata = open(path+"/filelists/metadata.csv", 'w', encoding='utf-8')

    for i in range(scriptEndPoint):
        fileName = timeSeries.readline()
        fileName = fileName.split('/')
        fileName = fileName[-1].strip('\n')
        fileName = fileName[:-4]
        # print(fileName)

        scriptContent = openCSV.readline()
        scriptContent = scriptContent.split('\t')
        scriptContent = scriptContent[0]+"\n"
        # print(scriptContent)

        contents = fileName + "|" + scriptContent
        # print(fileName + "|" + scriptContent)
        metadata.write(contents)
    
    timeSeries.close()
    openCSV.close()
    metadata.close()

    # for i in range(scriptEndPoint):
    #     print(i)
    ## script.csv를 열어서 한줄 가져오고 wav파일 일치시켜주고 (시간순 정렬이 가능한지 확인할것)
    ## ls -tr *.wav >> timeseries.log로 시간순으로 파일을 정렬하고
    ## 이를 한줄씩 읽어 script.csv를 복사해와서 2열에 차례대로 추가해주면 되지않을까?

    return id
