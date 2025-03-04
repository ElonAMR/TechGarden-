const express = require('express');
const fs = require("node:fs");
const router = express.Router();


router.get('/',(res,req)=>{
    console.log(`hello elon`);
});

router.get('/state',(res,req)=>{
    let data=JSON.parse(fs.readFileSync("Inside_information.json"));
    data={
        state:data.state,
        date:new Date()
    }
    res.JSON(data);

});

router.get('/dataMode' ,(req, res)=>{
    const {state} = req.query;
    let data=JSON.parse(fs.readFileSync("Inside_information.json"));
    res.json(data[state]);
})




module.exports=router;