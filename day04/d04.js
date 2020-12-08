const fs = require('fs')
fs.readFile('input', 'utf8' , (err, data) => {
  if (err) {
    console.error(err);
    return;
  }
  let passports_string = data.split("\n\n")
  let passports = [];
  for (let i of passports_string) {
      let current = {"string":i};
      var temp = i.replace("\n", " ");
      temp = temp.replace("\r", " ");
      temp = temp.replace("\n", " ");
      temp = temp.replace("\n", " ");
      temp = temp.replace("\n", " ");
      temp = temp.replace("\n", " ");
      // WHAT THE HELL IS GOING ON WHY DO I NEED TO REPLACE \n
      // SO MANY TIMES TO GET THE RIGHT NUMBER??????
      temp = temp.split(" ")
      for (let field of temp) {
          if (field.length > 3) {
            pair = field.split(":");
            current[pair[0]] = pair[1];
          }
      }
      passports[passports.length] = current;
  }
  passports.map((passport) => {
      const validity = passport.hasOwnProperty("byr")
        && passport.hasOwnProperty("iyr")
        && passport.hasOwnProperty("eyr")
        && passport.hasOwnProperty("hgt")
        && passport.hasOwnProperty("hcl")
        && passport.hasOwnProperty("ecl")
        && passport.hasOwnProperty("pid");
      passport["valid"] = validity;
      return passport;
  });
  console.log(passports.length);
  const valid_list = passports.filter( (passport) => passport.valid)
//  valid_list.map((passport) => {
//      const validity = true 
//        && passport.byr >= 1920 
//        && passport.byr <= 2002
//        && passport.iyr >= 2010 
//        && passport.iyr <= 2020
//        && passport.eyr >= 2020
//        && passport.eyr <= 2030
//        && passport.hgt = 
//        && passport.hasOwnProperty("eyr")
//        && passport.hasOwnProperty("hgt")
//        && passport.hasOwnProperty("hcl")
//        && passport.hasOwnProperty("ecl")
//        && passport.hasOwnProperty("pid");
//      passport["valid"] = validity;
//      return passport;
//  });
  console.log(valid_list.length);
})

