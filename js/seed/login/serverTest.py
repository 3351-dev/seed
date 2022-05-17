import uvicorn

if __name__ == "__main__":
    uvicorn.run(
            app="serverRecording:app",
            host="192.168.20.252",
            port=8000,
            reload=True,
            ssl_keyfile="/home/aiserver/ai/ssl/new_ssl/key.pem",
            ssl_certfile="/home/aiserver/ai/ssl/new_ssl/total.pem"
            )

