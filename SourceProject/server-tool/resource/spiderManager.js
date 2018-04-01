function init(){
    $.get("http://localhost:8001/get_task", function(data){
        var datas = []

        jsonData = JSON.parse(data)
        for (var ckey in jsonData){
            for (var skey in jsonData[ckey]["spiders"]){
                var data = {"clientname":"", "spidername":"", "items":[]}
                data["clientname"] = jsonData[ckey]["client-id"].substring(0, 6);
                data["spidername"] = jsonData[ckey]["spiders"][skey]["spider-name"]
                for (var item in jsonData[ckey]["spiders"][skey]["items"]){
                    var time = jsonData[ckey]["spiders"][skey]["items"][item]["time"]
                    var value = jsonData[ckey]["spiders"][skey]["items"][item]["value"]

                    var one = {}
                    one["name"] = time
                    one["value"] = [time, parseInt(value)]

                    data["items"].push(one)
                }
                datas.push(data)
            }
        }

        //console.log(datas)
        //return

        var myChart = echarts.init(document.getElementById('spider-chart'));

        var option = {
            title: { text: 'spider运行监控', },
            tooltip: { trigger: 'axis', },
            legend: { data:[] },
            toolbox: {
                show: true,
                feature: {
                    dataZoom: { yAxisIndex: 'none' },
                    dataView: {readOnly: false},
                    magicType: {type: ['line', 'bar']},
                    restore: {},
                    saveAsImage: {}
                }
            },
            xAxis:  { type: 'time', },
            yAxis: {
                type: 'value',
                axisLabel: { formatter: '{value} 个' }
            },
            series: []
        };
        for (var data in datas){
            label = datas[data]["clientname"] + ":" + datas[data]["spidername"]
            option.legend.data.push(label)
            var tmp = {}
            tmp["name"] = label
            tmp["type"] = "line"
            tmp["data"] = datas[data]["items"]
            option.series.push(tmp)
        }

        myChart.setOption(option);
    })
}
init()
self.setInterval("init()", 3000);
