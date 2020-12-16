const filee = require('fs')

filee.readFile('input', 'utf8' , (err, data) => {
    if (err) {
        console.error(err);
        return;
    }
    let groups = data.split('\n\n');
    let parsed = groups.map(x => x.split('\n'));
    partOne(parsed);
    partTwo(parsed);
})

function stringParser(inputString) {
    dict = {};
    for (const c of inputString) {
        if (!(c in dict)) {
            dict[c] = 0;
        }
        dict[c] = dict[c] + 1;
    }
    return dict;
}

function consensusCount(groupDict, numPeople) {
    let count = 0;
    for (const [key, value] of Object.entries(groupDict)) {
        if (value == numPeople) {
            count++;
        }
    }
    return count;
}

function partOne(parsedTree) {
    let groups = parsedTree.map(x => x.join(''));
    noOfAnyoneQuestions = groups.map(x => Object.keys(stringParser(x)).length);
    console.log(noOfAnyoneQuestions .reduce((total, current) => current + total));
}

function partTwo(parsedTree) {
    let groupNumberOfPeople = parsedTree.map(x => x.length);
    let groups = parsedTree.map(x => x.join(''));
    groupDicts = groups.map(x => stringParser(x));

    let noOfEveryoneQn = 0;
    let val = 0;
    for (let i = 0; i < groupDicts.length; i++) {
        const groupDict = groupDicts[i];
        const numberOfPeople = groupNumberOfPeople[i];
        noOfEveryoneQn = noOfEveryoneQn + consensusCount(groupDict, numberOfPeople);
    }
    console.log(noOfEveryoneQn);
}
