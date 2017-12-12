function init(){
    $.get("http://localhost:8001/get_task", function(data){
        var datas = []

        jsonData = JSON.parse(data)
        for (var ckey in jsonData){
            for (var skey in jsonData[ckey]["spiders"]){
                var data = []
                for (var item in jsonData[ckey]["spiders"][skey]["items"]){
                    var time = jsonData[ckey]["spiders"][skey]["items"][item]["time"]
                    var value = jsonData[ckey]["spiders"][skey]["items"][item]["value"]

                    var one = {}
                    one["name"] = time
                    one["value"] = [time, parseInt(value)]

                    data.push(one)
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
        var i = 1
        for (var data in datas){
            option.legend.data.push(i.toString())
            var tmp = {}
            tmp["name"] = i.toString()
            tmp["type"] = "line"
            tmp["data"] = datas[data]
            option.series.push(tmp)
            i += 1
        }

        myChart.setOption(option);
    })
}
init()
self.setInterval("init()", 3000);
