import requests

# ----------------------------
# 1. Fill these values
# ----------------------------

CSRF_TOKEN = "YOUR_X_CSRF_TOKEN"
CODENC = "YOUR_CODENC_VALUE"

COOKIES = {
    "XSRF-TOKEN": "YOUR_XSRF_TOKEN",
    "intranet_alumno_session": "YOUR_SESSION",
    "mode": "dark",
    # add any other cookies you want from your browser
}

# ----------------------------
# 2. POST payload (your exact data)
# ----------------------------

payload = {
    "codenc": CODENC,

    "data[codpre-1][0][codblo]": 1,
    "data[codpre-1][0][codpre]": 1,
    "data[codpre-1][0][codalt]": 1,
    "data[codpre-1][0][puntaje]": 5,
    "data[codpre-1][0][value]": 1,

    "data[codpre-2][0][codblo]": 1,
    "data[codpre-2][0][codpre]": 2,
    "data[codpre-2][0][codalt]": 6,
    "data[codpre-2][0][puntaje]": 5,
    "data[codpre-2][0][value]": 6,

    "data[codpre-3][0][codblo]": 1,
    "data[codpre-3][0][codpre]": 3,
    "data[codpre-3][0][codalt]": 11,
    "data[codpre-3][0][puntaje]": 5,
    "data[codpre-3][0][value]": 11,

    "data[codpre-4][0][codblo]": 1,
    "data[codpre-4][0][codpre]": 4,
    "data[codpre-4][0][codalt]": 16,
    "data[codpre-4][0][puntaje]": 5,
    "data[codpre-4][0][value]": 16,

    "data[codpre-5][0][codblo]": 2,
    "data[codpre-5][0][codpre]": 5,
    "data[codpre-5][0][codalt]": 21,
    "data[codpre-5][0][puntaje]": 5,
    "data[codpre-5][0][value]": 21,

    "data[codpre-6][0][codblo]": 2,
    "data[codpre-6][0][codpre]": 6,
    "data[codpre-6][0][codalt]": 26,
    "data[codpre-6][0][puntaje]": 5,
    "data[codpre-6][0][value]": 26,

    "data[codpre-7][0][codblo]": 2,
    "data[codpre-7][0][codpre]": 7,
    "data[codpre-7][0][codalt]": 31,
    "data[codpre-7][0][puntaje]": 5,
    "data[codpre-7][0][value]": 31,

    "data[codpre-8][0][codblo]": 2,
    "data[codpre-8][0][codpre]": 8,
    "data[codpre-8][0][codalt]": 36,
    "data[codpre-8][0][puntaje]": 5,
    "data[codpre-8][0][value]": 36,

    "data[codpre-9][0][codblo]": 3,
    "data[codpre-9][0][codpre]": 9,
    "data[codpre-9][0][codalt]": 41,
    "data[codpre-9][0][puntaje]": 5,
    "data[codpre-9][0][value]": 41,

    "data[codpre-10][0][codblo]": 3,
    "data[codpre-10][0][codpre]": 10,
    "data[codpre-10][0][codalt]": 46,
    "data[codpre-10][0][puntaje]": 5,
    "data[codpre-10][0][value]": 46,

    "data[codpre-11][0][codblo]": 3,
    "data[codpre-11][0][codpre]": 11,
    "data[codpre-11][0][codalt]": 51,
    "data[codpre-11][0][puntaje]": 5,
    "data[codpre-11][0][value]": 51,

    "data[codpre-12][0][codblo]": 3,
    "data[codpre-12][0][codpre]": 12,
    "data[codpre-12][0][codalt]": 56,
    "data[codpre-12][0][puntaje]": 5,
    "data[codpre-12][0][value]": 56,
}

# ----------------------------
# 3. Headers
# ----------------------------

headers = {
    "Accept": "application/json, text/javascript, */*; q=0.01",
    "Content-Type": "application/x-www-form-urlencoded; charset=UTF-8",
    "X-Requested-With": "XMLHttpRequest",
    "X-CSRF-TOKEN": CSRF_TOKEN,
    "Origin": "https://alumnos.uni.edu.pe",
    "Referer": "https://alumnos.uni.edu.pe/encuestas/docente/PUT_YOUR_REFERER_HERE",
}

# ----------------------------
# 4. Send request
# ----------------------------

url = "https://alumnos.uni.edu.pe/encuestas/save"

response = requests.post(url, headers=headers, cookies=COOKIES, data=payload)

print("Status:", response.status_code)
print("Response:", response.text)
