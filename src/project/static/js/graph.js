
function loadJson(selector) {
    return JSON.parse($(selector).attr('data_json'));
}

$(document).ready(function () {
    let jsonData = loadJson('#jsonData');
    let data = jsonData.map((item) => item.y);
    let labels = jsonData.map((item) => item.x);

    let config = {
        type: 'line',
        data: {
            labels: labels,
            datasets: [
                {
                    label: 'chart',
                    backgroundColor: 'black',
                    borderColor: 'lightblue',
                    data: data,
                    fill: false,
                    spanGaps: 3
                }
            ]
        },
        options: {
            responsive: true,
            scales : {
                y : {
                    min: -1,
                    max: 1,
                }
            }
        }
    };

    var ctx = document.getElementById('chart').getContext('2d');
    window.myLine = new Chart(ctx, config);
});


