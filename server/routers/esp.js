const express = require('express');
const router = express.Router();
const fs=require('fs');
const db = require('../models/dataBase')

router.get('/',async (req,res)=>{
    try{
        const  {temp , light , moisture} = req.query;
        console.log("temp = "+temp + ", light = "+light +", moisture = "+moisture);
        const id_threes = 1;

        await db.execute(
            `INSERT INTO dataSensors (id_threes, name_sensor, avg, date, isRunning) VALUES 
                (?, 'temperature', ?, NOW(), 1),
                (?, 'light', ?, NOW(), 1),
                (?, 'moisture', ?, NOW(), 1)`,
            [id_threes, temp, id_threes, light, id_threes, moisture]
        );
        res.status(200).json({ message: "Data received and stored" });
    }catch (error){
        console.log(error);
        res.status(500).json({ message: "Error storing data" });
    }
});

router.get('/state',(req,res)=>{
    let data = JSON.parse(fs.readFileSync("Inside_information.json", "utf8"));

    data.shabbat.currentTimeHour = new Date().getHours().toString();

    fs.writeFileSync("Inside_information.json", JSON.stringify(data), 'utf8');

    res.json(data.state);
});

router.get('/dataMode' ,(req, res)=>{
    const {state} = req.query;
    let data = JSON.parse(fs.readFileSync("Inside_information.json", "utf8"));
    res.json(data[state]);
})




module.exports=router;