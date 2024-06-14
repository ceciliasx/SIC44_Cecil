from flask import Flask, request, jsonify

app = Flask(__name__)
data = []

@app.route('/trial/hello', methods=['POST'])
def post():
    temp = request.args.get("temp")
    humid = request.args.get("humidness")
   
    subData = {"temp": temp, "humidness": humid}
    
    data.append(subData)
   
    return 'Yay!! Saved to server!:D'

@app.route('/trial/hello', methods=['GET'])

def get():
    return jsonify(data)

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
